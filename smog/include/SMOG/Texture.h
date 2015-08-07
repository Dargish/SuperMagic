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
			FLOAT_32,
			DEPTH_32
		};

		Texture(
			size_t width = 0, 
			size_t height = 0, 
			size_t channels = 4, 
			Format format = UNSIGNED_BYTE_8,
			bool isSRGB = false);

		virtual ~Texture();

		void deleteBuffer();

		uint buffer() const;

		void bind() const;
		void unbind() const;

		// Getters
		size_t width() const;
		size_t height() const;
		size_t channels() const;
		Format format() const;
		bool isSRGB() const;

		// Setters
		void setSize(size_t width, size_t height);
		void setChannels(size_t channels);
		void setFormat(Format format);
		void setIsSRGB(bool isSRGB);
		void setData(const void* data = NULL, int level = 0);

	private:
		uint glInternalFormat() const;
		uint glFormat() const;
		uint glDataType() const;

		uint m_buffer;
		size_t m_width, m_height, m_channels;
		Format m_format;
		bool m_isSRGB;
	};


	class SMOGAPI DepthTexture : public Texture
	{
	public:
		DepthTexture(size_t width = 0, size_t height = 0);
	};


	class SMOGAPI FileTexture : public Texture
	{
	public:
		FileTexture(const std::string& filename);

		const std::string& filename() const;

	private:
		std::string m_filename;
	};
}