#include <SMOG/ShaderProgram.h>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


SMOG_NAMESPACE_ENTER
{
	ShaderProgram::ShaderProgram() :
		m_linked(false), m_program(0)
	{

	}

	uint ShaderProgram::program()
	{
		if (m_program == 0)
		{
			m_program = glCreateProgram();
		}
		return m_program;
	}

	void ShaderProgram::clear()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	void ShaderProgram::attach(const Shader& shader)
	{
		if (m_linked)
		{
			ERROR("Cannot add shader to program that has already been linked");
		}
		glAttachShader(program(), shader.shader());
	}

	void ShaderProgram::link()
	{
		if (m_linked)
		{
			ERROR("Shader program has already been linked");
		}
		glLinkProgram(program());
		m_linked = true;
	}

	void ShaderProgram::use() const
	{
		if (!m_linked)
		{
			ERROR("Shader program must be linked before use");
		}
		glUseProgram(m_program);
	}

	void ShaderProgram::set(const std::string& name, float value) const
	{
		if (!m_linked)
		{
			ERROR("Shader program must be linked before setting values");
		}
		int loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform1f(loc, value);
		}	
	}

	void ShaderProgram::set(const std::string& name, const RGB& value) const
	{
		if (!m_linked)
		{
			ERROR("Shader program must be linked before setting values");
		}
		int loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform3fv(loc, 1, &value.r);
		}		
	}

	void ShaderProgram::set(const std::string& name, const Matrix4& value) const
	{
		if (!m_linked)
		{
			ERROR("Shader program must be linked before setting values");
		}
		int loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
		}		
	}

	void ShaderProgram::set(const std::string& name, const Texture& texture, int textureUnit /*= 0*/) const
	{
		if (!m_linked)
		{
			ERROR("Shader program must be linked before setting values");
		}
		int loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			texture.bind();
			glUniform1i(loc, textureUnit);
		}
	}
}