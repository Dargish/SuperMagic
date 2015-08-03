#include <SMOG/VertexBuffer.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	VertexBuffer::VertexBuffer() :
		m_vbo(0), m_type(0)
	{
		glGenBuffers(1, &m_vbo);
	}

	uint VertexBuffer::buffer() const
	{
		return m_vbo;
	}

	uint VertexBuffer::type() const
	{
		return m_type;
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	template<>
	uint VertexBuffer::glType<char>() const
	{
		return GL_BYTE;
	}

	template<>
	uint VertexBuffer::glType<uchar>() const
	{
		return GL_UNSIGNED_BYTE;
	}

	template<>
	uint VertexBuffer::glType<short>() const
	{
		return GL_SHORT;
	}

	template<>
	uint VertexBuffer::glType<ushort>() const
	{
		return GL_UNSIGNED_SHORT;
	}

	template<>
	uint VertexBuffer::glType<int>() const
	{
		return GL_INT;
	}

	template<>
	uint VertexBuffer::glType<uint>() const
	{
		return GL_UNSIGNED_INT;
	}

	template<>
	uint VertexBuffer::glType<float>() const
	{
		return GL_FLOAT;
	}

	template<>
	uint VertexBuffer::glType<double>() const
	{
		return GL_DOUBLE;
	}

	void VertexBuffer::bufferData(
		size_t size,
		void* data,
		Usage::Frequency frequency /*= Usage::kStatic*/,
		Usage::Access access /*= Usage::kDraw*/)
	{
		GLenum usage = 0;
		switch(frequency)
		{
			case Usage::kStream:
				switch(access)
				{
					case Usage::kDraw:
						usage = GL_STREAM_DRAW;
						break;
					case Usage::kRead:
						usage = GL_STREAM_READ;
						break;
					case Usage::kCopy:
						usage = GL_STREAM_COPY;
						break;
				}
				break;
			case Usage::kStatic:
				switch(access)
				{
					case Usage::kDraw:
						usage = GL_STATIC_DRAW;
						break;
					case Usage::kRead:
						usage = GL_STATIC_READ;
						break;
					case Usage::kCopy:
						usage = GL_STATIC_COPY;
						break;
				}
				break;
			case Usage::kDynamic:
				switch(access)
				{
					case Usage::kDraw:
						usage = GL_DYNAMIC_DRAW;
						break;
					case Usage::kRead:
						usage = GL_DYNAMIC_READ;
						break;
					case Usage::kCopy:
						usage = GL_DYNAMIC_COPY;
						break;
				}
				break;
		}
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}
}