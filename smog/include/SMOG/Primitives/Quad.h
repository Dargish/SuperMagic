#pragma once

#include <SMOG/Mesh.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Quad : public Mesh
	{
	public:
		Quad();

		virtual void draw() const;
	};
}