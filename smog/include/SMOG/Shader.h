#pragma once

#include <SMOG/SMOG.h>

#include <string>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Shader
	{
	public:
		enum Type
		{
			kInvalid = 0,
			kVertex,
			kFragment
		};

		Shader(const std::string& filePath, Type type);

		uint shader() const;

	private:
		uint m_shader;
		Type m_type;
	};
}