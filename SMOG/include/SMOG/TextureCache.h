#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/Texture.h>

#include <memory>
#include <map>


SMOG_NAMESPACE_ENTER
{
	class TextureLoader
	{
	public:
		virtual bool load(FileTexture& texture) const = 0;
	};

	class TextureCache
	{
	public:
		static TextureCache* Instance();

		template <typename T>
		static void RegisterLoader();

		FileTexture& load(const std::string& filename);

		static FileTexture& Load(const std::string& filename);

		void cleanUp();

		static void CleanUp();

	private:
		static std::unique_ptr<TextureCache> s_instance;
		std::unique_ptr<TextureLoader> m_loader;

		typedef std::map<std::string, FileTexture> Cache;
		Cache m_cache;
	};

	template <typename T>
	void TextureCache::RegisterLoader()
	{
		Instance()->m_loader.reset(new T);
	}
}