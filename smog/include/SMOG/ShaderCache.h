#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/Shader.h>

#include <memory>
#include <map>


SMOG_NAMESPACE_ENTER
{
	class ShaderCache
	{
	public:
		static ShaderCache* Instance();

		Shader& load(const std::string& filename, Shader::Type type);

		static Shader& Load(const std::string& filename, Shader::Type type);

	private:
		static std::unique_ptr<ShaderCache> s_instance;

		typedef std::map<std::string, Shader> Cache;
		Cache m_cache;
	};
}