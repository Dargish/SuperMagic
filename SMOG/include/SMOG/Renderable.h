#pragma once

#include <SMOG/SMOG.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Renderable
	{
	public:
		Renderable();
		virtual ~Renderable();
		
		virtual void draw() const = 0;
	};
}