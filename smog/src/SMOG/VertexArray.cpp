#include <SMOG/VertexArray.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	VertexArray::VertexArray() :
		m_vao(0), m_count(0)
	{
		glGenVertexArrays(1, &m_vao);
	}

	uint VertexArray::vao() const
	{
		return m_vao;
	}

	uint VertexArray::count() const
	{
		return m_count;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_vao);
	}

	void VertexArray::addBuffer(
		const VertexBuffer& buffer,
		int componentSize,
		bool normalised /*= false*/,
		size_t stride /*= 0*/,
		void* offset /*= NULL*/)
	{
		bind();
		glEnableVertexAttribArray(m_count);
		buffer.bind();
		glVertexAttribPointer(
			m_count,
			componentSize,
			(GLenum)buffer.type(),
			normalised,
			stride,
			offset);
		++m_count;
	}
}