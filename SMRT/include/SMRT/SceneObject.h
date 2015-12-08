#pragma once

#include <SMRT/SMRT.h>
#include <SMRT/Collider.h>

SMRT_NAMESPACE_ENTER
{
	class SceneObject
	{
	public:
		SceneObject();
		SceneObject(const SceneObject& other);
		~SceneObject();

		SceneObject& operator=(const SceneObject& other);

		Transform& transform();
		const Transform& transform() const;

		bool intersect(const Ray& ray, float& distance);

		Collider& collider();
		const Collider& collider() const;
		void setCollider(Collider* collider);

	private:
		Transform m_transform;
		Collider* m_collider;
	};
}