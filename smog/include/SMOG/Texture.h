#pragma once

#include <SMOG/SMOG.h>

#include <vector>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Texture
	{
	public:
		Texture();
		Texture(const std::string& filename);
		Texture(size_t width, size_t height, size_t channels = 4);

		void deleteBuffer();

		const std::string& filename() const;

		void bind() const;

		int internalFormat() const;

		uint format() const;

		uint dataType() const;

		void setSize(size_t width, size_t height);

		void setChannels(size_t channels);

		void setData(const void* data, int level = 0);

	private:
		uint m_buffer;
		size_t m_width, m_height, m_channels;
		std::string m_filename;
	};
}