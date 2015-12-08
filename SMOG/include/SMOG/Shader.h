#pragma once

#include <SMOG/SMOG.h>


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

		Shader(Type type = kInvalid);
		Shader(const std::string& filename, Type type);

		void load(const std::string& filename);

		uint shader() const;

	private:
		uint m_shader;
		Type m_type;
	};
}