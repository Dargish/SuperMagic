#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/Shader.h>
#include <SMOG/Texture.h>

#include <deque>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI ShaderProgram
	{
	public:
		ShaderProgram();

		uint program();

		void clear();

		void attach(const Shader& shader);

		void link();

		void use() const;

		void set(const std::string& name, float value) const;
		void set(const std::string& name, const RGB& value) const;
		void set(const std::string& name, const Matrix4& value) const;
		void set(const std::string& name, const Texture& texture, int textureUnit = 0) const;

	private:
		bool m_linked;
		uint m_program;
	};
}