#include <SMOG/Texture.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	Texture::Texture(
		size_t width /*= 0*/,
		size_t height /*= 0*/,
		size_t channels /*= 4*/, 
		Format format /*= UNSIGNED_BYTE_8*/,
		bool srgb /*= false*/
		) :
		m_buffer(0),
		m_width(width),
		m_height(height),
		m_channels(channels),
		m_format(format),
		m_srgb(srgb)
	{
		glGenTextures(1, &m_buffer);
	}

	void Texture::deleteBuffer()
	{
		glDeleteTextures(1, &m_buffer);
		m_buffer = 0;
	}

	void Texture::bind() const
	{
		if (m_buffer == 0)
		{
			ERROR("Cannot bind deleted texture");
		}
		glBindTexture(GL_TEXTURE_2D, m_buffer);
	}

	size_t Texture::width() const
	{
		return m_width;
	}

	size_t Texture::height() const
	{
		return m_height;
	}

	size_t Texture::channels() const
	{
		return m_channels;
	}

	Texture::Format Texture::format() const
	{
		return m_format;
	}

	bool Texture::srgb() const
	{
		return m_srgb;
	}


	// Setters
	void Texture::setSize(size_t width, size_t height)
	{
		m_width = width;
		m_height = height;
	}

	void Texture::setChannels(size_t channels)
	{
		m_channels = channels;
	}

	void Texture::setFormat(Format format)
	{
		m_format = format;
	}

	void Texture::setSRGB(bool srgb)
	{
		m_srgb = srgb;
	}

	void Texture::setData(const void* data, int level /*= 0*/)
	{
		bind();
		glTexImage2D(
			GL_TEXTURE_2D,
			level,
			glInternalFormat(),
			m_width,
			m_height,
			0,
			glFormat(),
			glDataType(),
			data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	uint Texture::glInternalFormat() const
	{
		switch(m_channels)
		{
			case 1:
				switch(m_format)
				{
					case UNSIGNED_BYTE_8:
						return GL_R8;
					case SHORT_16:
						return GL_R16F;
					case FLOAT_32:
						return GL_R32F;
				}
			case 2:
				switch(m_format)
				{
					case UNSIGNED_BYTE_8:
						return GL_RG8;
					case SHORT_16:
						return GL_RG16F;
					case FLOAT_32:
						return GL_RG32F;
				}
			case 3:
				switch(m_format)
				{
					case UNSIGNED_BYTE_8:
						if (m_srgb)
						{
							return GL_SRGB8;
						}
						else
						{
							return GL_RGB8;
						}
					case SHORT_16:
						return GL_RGB16F;
					case FLOAT_32:
						return GL_RGB32F;
				}
			case 4:
				switch(m_format)
				{
					case UNSIGNED_BYTE_8:
						if (m_srgb)
						{
							return GL_SRGB8_ALPHA8;
						}
						else
						{
							return GL_RGBA8;
						}
					case SHORT_16:
						return GL_RGBA16F;
					case FLOAT_32:
						return GL_RGBA32F;
				}
			default:
				ERROR("Unhandled channel count");
		}
	}

	uint Texture::glFormat() const
	{
		switch(m_channels)
		{
			case 1:
				return GL_R;
			case 2:
				return GL_RG;
			case 3:
				return GL_RGB;
			case 4:
				return GL_RGBA;
			default:
				ERROR("Unhandled channel count");
		}
	}

	uint Texture::glDataType() const
	{
		switch(m_format)
		{
			case UNSIGNED_BYTE_8:
				return GL_UNSIGNED_BYTE;
			case SHORT_16:
				return GL_SHORT;
			case FLOAT_32:
				return GL_FLOAT;
			default:
				ERROR("Unhandled format type");
		}
	}
}