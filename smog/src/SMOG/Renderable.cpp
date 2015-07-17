#include <SMOG/Renderable.h>

SMOG_NAMESPACE_ENTER
{
	Renderable::~Renderable()
	{
		
	}

	Matrix4& Renderable::worldMatrix()
	{
		return m_worldMatrix;
	}
	
	const Matrix4& Renderable::worldMatrix() const
	{
		return m_worldMatrix;
	}
}