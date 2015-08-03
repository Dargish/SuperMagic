#include <SMOG/Mesh.h>


SMOG_NAMESPACE_ENTER
{
	Mesh::Mesh()
	{
		
	}

	Mesh::~Mesh()
	{
		
	}

	VertexBuffer& Mesh::vbo()
	{
		return m_vertexBuffer;
	}

	const VertexBuffer& Mesh::vbo() const
	{
		return m_vertexBuffer;
	}

	VertexArray& Mesh::vao()
	{
		return m_vertexArray;
	}

	const VertexArray& Mesh::vao() const
	{
		return m_vertexArray;
	}
}