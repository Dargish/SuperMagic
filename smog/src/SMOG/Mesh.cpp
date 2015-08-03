#include <SMOG/Mesh.h>


SMOG_NAMESPACE_ENTER
{
	Mesh::Mesh()
	{
		
	}

	Mesh::~Mesh()
	{
		
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