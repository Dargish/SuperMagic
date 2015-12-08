#pragma once

#include <SMRT/Collider.h>

SMRT_NAMESPACE_ENTER
{
	class Sphere : public Collider
	{
	public:
		Sphere(float radius = 1.0f);

		virtual bool intersect(const Ray& ray, float& distance);

		virtual Collider* copy() const;

	private:
		float m_radius;
	};
}