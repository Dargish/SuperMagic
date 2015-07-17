#include <SMOG/SMOG.h>

#include <GL/glew.h>

#include <string>
#include <stdexcept>


SMOG_NAMESPACE_ENTER
{
	void initialiseGlew()
	{
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			throw std::runtime_error(
				std::string("glewInit failed:\n\t") + std::string((char*)glewGetErrorString(err)));
		}
	}
}