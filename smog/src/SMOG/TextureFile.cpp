#include <SMOG/TextureFile.h>

SMOG_NAMESPACE_ENTER
{
	TextureFile::TextureFile(const std::string& filename) :
		m_filename(filename)
	{

	}

	const std::string& TextureFile::filename() const
	{
		return m_filename;
	}
}