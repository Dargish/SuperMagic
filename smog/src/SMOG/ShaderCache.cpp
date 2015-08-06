#include <SMOG/ShaderCache.h>


SMOG_NAMESPACE_ENTER
{
	std::unique_ptr<ShaderCache> ShaderCache::s_instance;
	
	ShaderCache* ShaderCache::Instance()
	{
		if (s_instance.get() == NULL)
		{
			s_instance.reset(new ShaderCache);
		}
		return s_instance.get();
	}

	Shader& ShaderCache::load(const std::string& filename, Shader::Type type)
	{
		Cache::iterator found = m_cache.find(filename);
		if (found == m_cache.end())
		{
			return m_cache.emplace(
				filename, Shader(filename, type)).first->second;
		}
		return found->second;
	}

	Shader& ShaderCache::Load(const std::string& filename, Shader::Type type)
	{
		return Instance()->load(filename, type);
	}
}