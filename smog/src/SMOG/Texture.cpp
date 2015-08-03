#include <SMOG/Texture.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	Texture::Texture() :
		m_buffer(0), m_width(0), m_height(0), m_channels(4)
	{
		glGenTextures(1, &m_buffer);
	}
	
	Texture::Texture(const std::string& filename) :
		m_buffer(0), m_width(0), m_height(0), m_channels(4), m_filename(filename)
	{
		glGenTextures(1, &m_buffer);
	}

	Texture::Texture(size_t width, size_t height, size_t channels /*= 4*/) :
		m_buffer(0), m_width(width), m_height(height), m_channels(channels)
	{
		glGenTextures(1, &m_buffer);
	}

	void Texture::deleteBuffer()
	{
		glDeleteTextures(1, &m_buffer);
		m_buffer = 0;
	}

	const std::string& Texture::filename() const
	{
		return m_filename;
	}

	void Texture::bind() const
	{
		if (m_buffer == 0)
		{
			ERROR("Cannot bind deleted texture");
		}
		glBindTexture(GL_TEXTURE_2D, m_buffer);
	}

	int Texture::internalFormat() const
	{
		switch(m_channels)
		{
			case 1:
				return GL_R32F;
			case 3:
				return GL_SRGB8;
			case 4:
				return GL_SRGB8_ALPHA8;
			default:
				ERROR("Unhandled channel count");
		}
	}

	uint Texture::format() const
	{
		switch(m_channels)
		{
			case 1:
				return GL_R;
			case 3:
				return GL_BGR;
			case 4:
				return GL_BGRA;
			default:
				ERROR("Unhandled channel count");
		}
	}

	uint Texture::dataType() const
	{
		switch(m_channels)
		{
			case 1:
				return GL_FLOAT;
			case 3:
				return GL_UNSIGNED_BYTE;
			case 4:
				return GL_UNSIGNED_BYTE;
			default:
				ERROR("Unhandled channel count");
		}
	}

	void Texture::setSize(size_t width, size_t height)
	{
		m_width = width;
		m_height = height;
	}

	void Texture::setChannels(size_t channels)
	{
		m_channels = channels;
	}

	void Texture::setData(const void* data, int level /*= 0*/)
	{
		bind();
		glTexImage2D(
			GL_TEXTURE_2D,
			level,
			internalFormat(),
			m_width,
			m_height,
			0,
			format(),
			GL_UNSIGNED_BYTE,
			data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}