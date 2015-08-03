#pragma once

#include <SMOG/Renderable.h>
#include <SMOG/VertexBuffer.h>
#include <SMOG/VertexArray.h>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Mesh : public Renderable
	{
	public:
		Mesh();
		virtual ~Mesh();
		
		VertexArray& vao();
		const VertexArray& vao() const;

	private:
		VertexArray m_vertexArray;
	};
}