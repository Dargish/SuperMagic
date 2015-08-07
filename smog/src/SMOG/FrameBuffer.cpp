#include <SMOG/FrameBuffer.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	FrameBuffer::FrameBuffer(
		size_t width /*= 0*/,
		size_t height /*= 0*/) :
		m_fbo(0),
		m_width(width),
		m_height(height),
		m_depthTexture(width, height, 1, Texture::DEPTH_32)
	{
		glGenFramebuffers(1, &m_fbo);
		m_depthTexture.setData();
		bind();
		m_depthTexture.bind();
		glFramebufferTexture2D(
			GL_DRAW_FRAMEBUFFER,
			GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D,
			m_depthTexture.buffer(),
			0);
		m_depthTexture.unbind();
		ensureComplete();
		unbind();
	}

	void FrameBuffer::deleteBuffer()
	{
		glDeleteFramebuffers(1, &m_fbo);
		m_fbo = 0;
	}

	uint FrameBuffer::buffer() const
	{
		return m_fbo;
	}

	void FrameBuffer::bind() const
	{
		if (m_fbo == 0)
		{
			ERROR("Cannot bind deleted frame buffer");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void FrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	size_t FrameBuffer::width() const
	{
		return m_width;
	}

	size_t FrameBuffer::height() const
	{
		return m_height;
	}
	
	void FrameBuffer::setSize(size_t width, size_t height)
	{
		m_width = width;
		m_height = height;
	}

	const Texture& FrameBuffer::addTarget(
		const std::string& name,
		size_t channels,
		Texture::Format format)
	{
		std::pair<TargetMap::iterator, bool> pair = m_targetMap.emplace(
			name, Texture(m_width, m_height, channels, format));
		pair.first->second.setData();
		bind();
		pair.first->second.bind();
		glFramebufferTexture2D(
			GL_DRAW_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + m_targetMap.size() - 1,
			GL_TEXTURE_2D,
			pair.first->second.buffer(),
			0);
		pair.first->second.unbind();
		ensureComplete();
		unbind();
		return pair.first->second;
	}

	const Texture& FrameBuffer::target(const std::string& name) const
	{
		TargetMap::const_iterator found = m_targetMap.find(name);
		if (found == m_targetMap.end())
		{
			ERROR("Failed to find target " + name + " in frame buffer");
		}
		return found->second;
	}
	
	void FrameBuffer::ensureComplete() const
	{
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR("Frame buffer is not complete");
		}
	}
}