#include <SMOG/Mesh.h>

#include <GL/glew.h>

#include <stdexcept>

SMOG_NAMESPACE_ENTER
{
	Mesh::Mesh() :
		m_vbo(0)
	{
		
	}

	Mesh::~Mesh()
	{
		
	}

	uint Mesh::vbo()
	{
		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}
		return m_vbo;
	}

	uint Mesh::vbo() const
	{
		if (m_vbo == 0)
		{
			std::runtime_error("Vertex Buffer Object is not generated");
		}
		return m_vbo;
	}

	uint Mesh::vao()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}
		return m_vao;
	}

	uint Mesh::vao() const
	{
		if (m_vao == 0)
		{
			std::runtime_error("Vertex Attribute Object is not generated");
		}
		return m_vao;
	}
}