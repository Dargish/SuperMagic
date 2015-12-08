#include <SMOG/SMOG.h>

#include <GL/glew.h>

#include <iostream>
#include <execinfo.h>
#include <unistd.h>


SMOG_NAMESPACE_ENTER
{
	void initialiseGlew()
	{
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			ERROR(
				std::string("glewInit failed:\n\t") + std::string((char*)glewGetErrorString(err)));
		}
	}

	void checkGLErrors()
	{
		GLenum err = glGetError();
		switch (err)
		{
		case GL_INVALID_ENUM:
			WARN("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_VALUE:
			WARN("GL_INVALID_VALUE: A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_OPERATION:
			WARN("GL_INVALID_OPERATION: The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			WARN("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_OUT_OF_MEMORY:
			WARN("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
			break;
		case GL_STACK_UNDERFLOW:
			WARN("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.");
			break;
		case GL_STACK_OVERFLOW:
			WARN("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.");
			break;
		case GL_NO_ERROR:
		default:
			return;
		}
	}

	void printBacktrace()
	{
		void* array[16];
		size_t size;

		size = backtrace(array, 16);

		std::cerr << "Back Trace:" << std::endl;
		backtrace_symbols_fd(array, size, STDERR_FILENO);
	}

	void printError(const std::string& message)
	{
		printBacktrace();
		std::cerr << "SMOG::Error: " << message << std::endl;
	}

	void printWarning(const std::string& message)
	{
		std::cerr << "SMOG::Warning: " << message << std::endl;
	}

	void printNotice(const std::string& message)
	{
		std::cerr << "SMOG::Notice: " << message << std::endl;
	}
}