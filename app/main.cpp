// SMOG
#include <SMOG/SMOG.h>
#include <SMOG/Viewport.h>
#include <SMOG/Shader.h>
#include <SMOG/ShaderProgram.h>
#include <SMOG/Texture.h>
#include <SMOG/TextureCache.h>
#include <SMOG/Material.h>
#include <SMOG/RenderScene.h>
#include <SMOG/Primitives/Triangle.h>

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

struct RenderableComponent : public Renderable, public Component
{
	SMSM_TYPENAME(RenderableComponent);

	RenderableComponent()
	{

	}

	virtual void draw() const
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
	virtual bool load(TextureFile& texture) const
	{
		sf::Image image;
		if (!image.loadFromFile(texture.filename()))
		{
			return false;
		}
		sf::Vector2u imageSize = image.getSize();
		texture.setSize(imageSize.x, imageSize.y);
		texture.setChannels(4);
		texture.setData(image.getPixelsPtr());
		return true;
	}
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

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
            else if (event.type == sf::Event::Resized)
            {
            	viewport.resize(event.size.width, event.size.height);
            }
		}
		viewport.clear();

		// Update
		scene.update(0.0f);

		// Draw
		for(SceneObjects::iterator sit = scene.begin(); sit != scene.end(); ++sit)
		{
			Components::iterator_range range = sit->components<RenderableComponent>();
			for(Components::iterator cit = range.begin; cit != range.end; ++cit)
			{
				cit->as<RenderableComponent>().draw();
			}
		}

		window.display();

#if 0
		checkGLErrors();
#endif
	}

	return 0;
}