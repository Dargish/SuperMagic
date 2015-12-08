#include <SMRT/Colliders/Sphere.h>

SMRT_NAMESPACE_ENTER
{
	Sphere::Sphere(float radius /*= 1.0f*/) :
		m_radius(radius)
	{

	}

	bool Sphere::intersect(const Ray& ray, float& distance)
	{
		(void)ray;
		(void)distance;
		return false;
	}

	Collider* Sphere::copy() const
	{
		return new Sphere(m_radius);
	}
}