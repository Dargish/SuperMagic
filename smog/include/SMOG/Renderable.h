#pragma once

#include <SMOG/SMOG.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Renderable
	{
	public:
		virtual ~Renderable();
		
		virtual void draw() const = 0;

		Matrix4& worldMatrix();
		const Matrix4& worldMatrix() const;

	private:
		Matrix4 m_worldMatrix;
	};
}