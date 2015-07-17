// SMOG
#include <SMOG/SMOG.h>
#include <SMOG/Viewport.h>
#include <SMOG/Shader.h>
#include <SMOG/ShaderProgram.h>
#include <SMOG/RenderScene.h>
#include <SMOG/Primitives/Triangle.h>

// SMSM
#include <SMSM/SceneObject.h>

// SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// STL
#include <iostream>

SMOG_NAMESPACE_USING
SMSM_NAMESPACE_USING

int main()
{
	sf::ContextSettings settings;
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;

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

	SceneObject sceneObject;

	std::cerr << "transform: " << sceneObject.transform().position().x << ", " <<
		sceneObject.transform().position().y << ", " <<
		sceneObject.transform().position().z << std::endl;

	std::cerr << "rotation: " << sceneObject.transform().rotation().x << ", " <<
		sceneObject.transform().rotation().y << ", " <<
		sceneObject.transform().rotation().z << ", " <<
		sceneObject.transform().rotation().w << std::endl;

	std::cerr << "scale: " << sceneObject.transform().scale().x << ", " <<
		sceneObject.transform().scale().y << ", " <<
		sceneObject.transform().scale().z << std::endl;

	Triangle triangle;

	ShaderProgram program;
	program.attach(Shader("install/share/shaders/color.vert", Shader::kVertex));
	program.attach(Shader("install/share/shaders/color.frag", Shader::kFragment));
	program.link();

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

		program.use();

		program.set("world", triangle.worldMatrix());

		sceneObject.transform().setWorldMatrix(triangle.worldMatrix());

		triangle.draw();

		window.display();
	}

	return 0;
}