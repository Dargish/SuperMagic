#pragma once

#include <SMOG/Mesh.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Triangle : public Mesh
	{
	public:
		Triangle();

		virtual void draw() const;
	};
}