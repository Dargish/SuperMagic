#include <SMRT/SceneObject.h>

SMRT_NAMESPACE_ENTER
{
	SceneObject::SceneObject() :
		m_collider(NULL)
	{

	}

	SceneObject::SceneObject(const SceneObject& other) :
		m_collider(other.m_collider->copy())
	{

	}

	SceneObject::~SceneObject()
	{
		if (m_collider != NULL)
		{
			delete m_collider;
		}
	}

	SceneObject& SceneObject::operator=(const SceneObject& other)
	{
		setCollider(other.m_collider->copy());
		return *this;
	}

	Transform& SceneObject::transform()
	{
		return m_transform;
	}

	const Transform& SceneObject::transform() const
	{
		return m_transform;
	}

	bool SceneObject::intersect(const Ray& ray, float& distance)
	{
		if (m_collider == NULL)
		{
			return false;
		}
		return m_collider->intersect(ray, distance);
	}

	Collider& SceneObject::collider()
	{
		return *m_collider;
	}

	const Collider& SceneObject::collider() const
	{
		return *m_collider;
	}

	void SceneObject::setCollider(Collider* collider)
	{
		if (m_collider != NULL)
		{
			delete m_collider;
		}
		m_collider = collider;
	}
}