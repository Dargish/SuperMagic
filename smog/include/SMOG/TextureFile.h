#pragma once

#include <SMOG/Texture.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI TextureFile : public Texture
	{
	public:
		TextureFile(const std::string& filename);

		const std::string& filename() const;

	private:
		std::string m_filename;
	};
}