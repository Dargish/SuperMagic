#include <SMOG/Shader.h>

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>


SMOG_NAMESPACE_ENTER
{
	Shader::Shader(const std::string& filePath, Type type) :
		m_shader(0), m_type(type)
	{
		std::ifstream in(filePath);
		std::stringstream buf;
		buf << in.rdbuf();
		std::string shaderText = buf.str();

		if (shaderText.empty())
		{
			throw std::runtime_error("Failed to load shader " + filePath);
		}

		switch(m_type)
		{
			case kVertex:
				m_shader = glCreateShader (GL_VERTEX_SHADER);
				break;
			case kFragment:
				m_shader = glCreateShader (GL_FRAGMENT_SHADER);
				break;
			default:
				throw std::runtime_error("Unknown shader type");
		}

		const char* shaderTextPtr = shaderText.c_str();
		glShaderSource(m_shader, 1, &shaderTextPtr, NULL);
		glCompileShader(m_shader);
		GLint result = GL_FALSE;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logLength = 0;
			glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLength);
			std::string log;
			log.resize(logLength);
			glGetShaderInfoLog(m_shader, logLength, &logLength, (GLchar*)log.c_str());

			GLint srcLength = 0;
			glGetShaderiv(m_shader, GL_SHADER_SOURCE_LENGTH, &srcLength);
			std::string src;
			src.resize(srcLength);
			glGetShaderSource(m_shader, srcLength, &srcLength, (GLchar*)src.c_str());
			std::cerr << src << "\n" << log << std::endl;
			throw std::runtime_error("Error compiling shader");
		}
	}

	uint Shader::shader() const
	{
		return m_shader;
	}
}