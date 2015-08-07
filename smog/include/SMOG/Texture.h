#pragma once

#include <SMOG/SMOG.h>

#include <vector>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Texture
	{
	public:
		enum Format
		{
			UNSIGNED_BYTE_8 = 0,
			SHORT_16,
			FLOAT_32
		};

		Texture(
			size_t width = 0, 
			size_t height = 0, 
			size_t channels = 4, 
			Format format = UNSIGNED_BYTE_8,
			bool srgb = false);

		void deleteBuffer();

		void bind() const;

		// Getters
		size_t width() const;
		size_t height() const;
		size_t channels() const;
		Format format() const;
		bool srgb() const;

		// Setters
		void setSize(size_t width, size_t height);
		void setChannels(size_t channels);
		void setFormat(Format format);
		void setSRGB(bool srgb);
		void setData(const void* data, int level = 0);

	private:
		uint glInternalFormat() const;
		uint glFormat() const;
		uint glDataType() const;

		uint m_buffer;
		size_t m_width, m_height, m_channels;
		Format m_format;
		bool m_srgb;
	};
}