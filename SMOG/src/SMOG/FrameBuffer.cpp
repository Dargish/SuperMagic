#include <SMOG/FrameBuffer.h>

#include <GL/glew.h>

#include <iostream>

SMOG_NAMESPACE_ENTER
{
	FrameBuffer::FrameBuffer(
		size_t width /*= 0*/,
		size_t height /*= 0*/) :
		m_fbo(0),
		m_dirty(true),
		m_width(width),
		m_height(height),
		m_depthTexture(width, height)
	{
		glGenFramebuffers(1, &m_fbo);
		m_depthTexture.setData();
	}

	void FrameBuffer::deleteBuffer()
	{
		glDeleteFramebuffers(1, &m_fbo);
		m_fbo = 0;
		for (TargetMap::iterator it = m_targetMap.begin(); it != m_targetMap.end(); ++it)
		{
			it->second.deleteBuffer();
		}
		m_depthTexture.deleteBuffer();
	}

	uint FrameBuffer::buffer() const
	{
		return m_fbo;
	}

	void FrameBuffer::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::bind() const
	{
		if (m_fbo == 0)
		{
			ERROR("Cannot bind deleted frame buffer");
		}
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		if (m_dirty)
		{
			resetBuffer();
		}

		size_t drawBufferSize = m_targetMap.size();
		if (drawBufferSize > 0)
		{
			std::vector<GLenum> drawBuffers(drawBufferSize);
			for (size_t i = 0; i < drawBufferSize; ++i)
			{
				drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			}
			glDrawBuffers(drawBufferSize, &drawBuffers.front());
		}
	}

	void FrameBuffer::bindForRead() const
	{
		if (m_fbo == 0)
		{
			ERROR("Cannot bind deleted frame buffer");
		}
 		unbind();
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	}

	void FrameBuffer::bindTargets(const ShaderProgram& program) const
	{
		for (TargetMap::const_iterator it = m_targetMap.begin(); it != m_targetMap.end(); ++it)
		{
			program.set(it->first, it->second);
		}
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
		m_dirty = true;
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
	
	void FrameBuffer::resetBuffer() const
	{
		std::cerr << "Resetting buffer" << std::endl;

		size_t attachment = 0;
		for (TargetMap::const_iterator it = m_targetMap.begin(); it != m_targetMap.end(); ++it)
		{
			it->second.bind();
			glFramebufferTexture2D(
				GL_DRAW_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0 + attachment,
				GL_TEXTURE_2D,
				it->second.buffer(),
				0);
			it->second.unbind();
			++attachment;
		}

		m_depthTexture.bind();
		glFramebufferTexture2D(
			GL_DRAW_FRAMEBUFFER,
			GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D,
			m_depthTexture.buffer(),
			0);
		m_depthTexture.unbind();

		ensureComplete();
		m_dirty = false;
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