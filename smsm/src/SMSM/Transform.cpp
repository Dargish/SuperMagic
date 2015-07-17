#include <SMSM/Transform.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>


SMSM_NAMESPACE_ENTER
{
	Transform::Transform() :
		m_scale(1, 1, 1)
	{

	}

	Vector3& Transform::position()
	{
		return m_position;
	}

	const Vector3& Transform::position() const
	{
		return m_position;
	}

	Quaternion& Transform::rotation()
	{
		return m_rotation;
	}

	const Quaternion& Transform::rotation() const
	{
		return m_rotation;
	}

	Vector3& Transform::scale()
	{
		return m_scale;
	}

	const Vector3& Transform::scale() const
	{
		return m_scale;
	}

	void Transform::setWorldMatrix(Matrix4& worldMatrix)
	{
		Matrix4 positionMtx = glm::translate(m_position);
		Matrix4 rotationMtx = glm::toMat4(m_rotation);
		Matrix4 scaleMtx = glm::scale(m_scale);
		worldMatrix = positionMtx * rotationMtx * scaleMtx;
	}
}