#include <SMOG/ShaderProgram.h>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>


SMOG_NAMESPACE_ENTER
{
	ShaderProgram::ShaderProgram() :
		m_linked(false), m_program(0)
	{
		m_program = glCreateProgram();
	}

	void ShaderProgram::attach(const Shader& shader)
	{
		if (m_linked)
		{
			throw std::runtime_error("Cannot add shader to program that has already been linked");
		}
		glAttachShader(m_program, shader.shader());
	}

	void ShaderProgram::link()
	{
		if (m_linked)
		{
			throw std::runtime_error("Shader program has already been linked");
		}
		glLinkProgram(m_program);
		m_linked = true;
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_program);
	}

	void ShaderProgram::set(const std::string& name, const Matrix4& value)
	{
		int loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
		}		
	}
}