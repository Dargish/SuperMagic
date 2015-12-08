// SMOG
#include <SMOG/SMOG.h>
#include <SMOG/Viewport.h>
#include <SMOG/Shader.h>
#include <SMOG/ShaderProgram.h>
#include <SMOG/Texture.h>
#include <SMOG/TextureCache.h>
#include <SMOG/Material.h>
#include <SMOG/RenderScene.h>
#include <SMOG/FrameBuffer.h>
#include <SMOG/Primitives/Triangle.h>
#include <SMOG/Primitives/Quad.h>


#include <GL/glew.h>

// SMSM
#include <SMSM/Scene.h>
#include <SMSM/Component.h>

// SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// STL
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>


SMOG_NAMESPACE_USING
SMSM_NAMESPACE_USING

struct RenderableComponent : public Component
{
	SMSM_TYPENAME(RenderableComponent);

	RenderableComponent()
	{

	}

	void draw() const
	{
		if (renderable)
		{
			material.program().use();
			material.program().set("world", sceneObject().transform().worldMatrix());
			renderable->draw();
		}
	}

	std::unique_ptr<Renderable> renderable;
	Material material;
};

class SFML_TextureLoader : public TextureLoader
{
public:
	virtual bool load(FileTexture& texture) const
	{
		sf::Image image;
		if (!image.loadFromFile(texture.filename()))
		{
			return false;
		}
		sf::Vector2u imageSize = image.getSize();
		texture.setSize(imageSize.x, imageSize.y);
		texture.setChannels(4);
		texture.setFormat(Texture::UNSIGNED_BYTE_8);
		texture.setIsSRGB(true);
		texture.setData(image.getPixelsPtr());
		return true;
	}
};

class GBuffer
{
public:
	enum Target
	{
		kDiffuse = 0,
		kTargetCount
	};

	GBuffer() :
		m_fbo(0),
		m_diffuse(0),
		m_depthTexture(0)
	{
		init();
	}

	void init()
	{
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_diffuse);
		glBindTexture(GL_TEXTURE_2D, m_diffuse);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA8,
			800,
			600,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL);
		glFramebufferTexture2D(
			GL_DRAW_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			m_diffuse,
			0);

		glGenTextures(1, &m_depthTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT32F,
			800,
			600,
			0,
			GL_DEPTH_COMPONENT,
			GL_FLOAT,
			NULL);
		glFramebufferTexture2D(
			GL_DRAW_FRAMEBUFFER,
			GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D,
			m_depthTexture,
			0);
		glBindTexture(GL_TEXTURE_2D, 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR("Frame buffer is not complete");
		}

		finish();
	}

	void writeTo() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	}

	void readFrom() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	}

	void finish() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	uint target(Target /*target*/) const
	{
		return m_diffuse;
	}

private:
	uint m_fbo;
	uint m_diffuse;
	uint m_depthTexture;
};

int main()
{
	sf::ContextSettings settings;
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;

	sf::Window window(sf::VideoMode(800, 600), "SMOG Test", sf::Style::Close, settings);

	sf::ContextSettings actualSettings = window.getSettings();
	std::cout << "Window created:\n" <<
		 "\tMajor Version: " << actualSettings.majorVersion << "\n" <<
		 "\tMinor Version: " << actualSettings.minorVersion << "\n" <<
		 "\tDepth Bits   : " << actualSettings.depthBits << "\n" <<
		 "\tStencil Bits : " << actualSettings.stencilBits << "\n" <<
		 "\tAntialiasing : " << actualSettings.antialiasingLevel << std::endl;

	window.setVerticalSyncEnabled(true);

	initialiseGlew();

	sf::Vector2u windowSize = window.getSize();
	Viewport viewport(windowSize.x, windowSize.y);

	TextureCache::RegisterLoader<SFML_TextureLoader>();

	Scene scene;

//	FrameBuffer frameBuffer(800, 600);
//	frameBuffer.addTarget("diffuse", 4, Texture::UNSIGNED_BYTE_8);

	GBuffer gbuffer;

	// Scene setup
	for (int i = 0; i < 4; ++i)
	{
		SceneObject& sceneObject = scene.createSceneObject();
		RenderableComponent& rendComp = sceneObject.createComponent<RenderableComponent>();
		rendComp.renderable.reset(new Triangle);
#if 1
		rendComp.material = Material::Load("install/share/materials/textured.mtl");
#else
		std::stringstream ss;
		ss << "install/share/materials/color" << i << ".mtl";
#if 1
		rendComp.material = Material::Load(ss.str());
#else
		rendComp.material = Material::Load("install/share/materials/color.mtl");
		rendComp.material.set("color", RGB(
			(i == 0 || i == 1) ? 1.0f : 0.0f,
			(i == 0 || i == 2) ? 1.0f : 0.0f,
			(i == 0 || i == 3) ? 1.0f : 0.0f));
		rendComp.material.save(ss.str());
#endif
#endif
		sceneObject.transform().position = Vector3(
			(i % 2) ? 0.5f : -0.5f,
			(i > 1) ? 0.5f : -0.5f,
			0.0f);
		sceneObject.transform().scale = Vector3(0.5f, 0.5f, 1.0f);
	}

	Material material = Material::Load("install/share/materials/debug_gbuffer.mtl");
	Quad quad;

	

	// Main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
            else if (event.type == sf::Event::Resized)
            {
            	viewport.resize(event.size.width, event.size.height);
            }
		}

		// Update
		scene.update(0.0f);

		// Bind the frame buffer
		//frameBuffer.bind();
		gbuffer.writeTo();
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		for(SceneObjects::iterator sit = scene.begin(); sit != scene.end(); ++sit)
		{
			Components::iterator_range range = sit->components<RenderableComponent>();
			for(Components::iterator cit = range.begin; cit != range.end; ++cit)
			{
				cit->as<RenderableComponent>().draw();
			}
		}
		glUseProgram(0);

		//frameBuffer.unbind();
		//frameBuffer.bindForRead();

		gbuffer.readFrom();
		
		glDisable(GL_DEPTH_TEST);
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		material.program().use();
		//frameBuffer.bindTargets(material.program());
		material.program().set("diffuse", Texture(gbuffer.target(GBuffer::kDiffuse)));
		quad.draw();
		glUseProgram(0);

		gbuffer.finish();

		//frameBuffer.unbind();

		window.display();

#if 1
		checkGLErrors();
#endif
	}
	
	uchar pixels[800*600*4];

//	const Texture& target = frameBuffer.target("diffuse");
//	target.bind();
	uint target = gbuffer.target(GBuffer::kDiffuse);
	glBindTexture(GL_TEXTURE_2D, target);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
//	target.unbind();

	sf::Image image;
	image.create(800, 600, pixels);
	image.saveToFile("screenshot.png");

	TextureCache::CleanUp();

#if 1
	checkGLErrors();
#endif

	return 0;
}