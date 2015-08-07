#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/TextureFile.h>

#include <memory>
#include <map>


SMOG_NAMESPACE_ENTER
{
	class TextureLoader
	{
	public:
		virtual bool load(TextureFile& texture) const = 0;
	};

	class TextureCache
	{
	public:
		static TextureCache* Instance();

		template <typename T>
		static void RegisterLoader();

		TextureFile& load(const std::string& filename);

		static TextureFile& Load(const std::string& filename);

		void cleanUp();

		static void CleanUp();

	private:
		static std::unique_ptr<TextureCache> s_instance;
		std::unique_ptr<TextureLoader> m_loader;

		typedef std::map<std::string, TextureFile> Cache;
		Cache m_cache;
	};

	template <typename T>
	void TextureCache::RegisterLoader()
	{
		Instance()->m_loader.reset(new T);
	}
}