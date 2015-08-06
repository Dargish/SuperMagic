#include <SMOG/TextureCache.h>


SMOG_NAMESPACE_ENTER
{
	std::unique_ptr<TextureCache> TextureCache::s_instance;
	
	TextureCache* TextureCache::Instance()
	{
		if (s_instance.get() == NULL)
		{
			s_instance.reset(new TextureCache);
		}
		return s_instance.get();
	}

	Texture& TextureCache::load(const std::string& filename)
	{
		if (m_loader.get() == NULL)
		{
			ERROR("A TextureLoader has not been registered");
		}
		else
		{
			Cache::iterator found = m_cache.find(filename);
			if (found == m_cache.end())
			{
				std::pair<Cache::iterator, bool> pair = m_cache.emplace(
					filename, Texture(filename));
				if (!m_loader->load(pair.first->second))
				{
					ERROR("Failed to load texture " + filename);
				}
				return pair.first->second;
			}
			return found->second;
		}
	}

	Texture& TextureCache::Load(const std::string& filename)
	{
		return Instance()->load(filename);
	}

	void TextureCache::cleanUp()
	{
		for (Cache::iterator it = m_cache.begin(); it != m_cache.end(); ++it)
		{
			it->second.deleteBuffer();
		}
	}

	void TextureCache::CleanUp()
	{
		Instance()->cleanUp();
	}
}