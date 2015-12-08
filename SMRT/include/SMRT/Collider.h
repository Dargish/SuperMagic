#pragma once

#include <SMRT/SMRT.h>

SMRT_NAMESPACE_ENTER
{
	class Collider
	{
	public:
		virtual ~Collider() {};

		virtual bool intersect(const Ray& ray, float& distance) = 0;

		virtual Collider* copy() const = 0;
	};
}