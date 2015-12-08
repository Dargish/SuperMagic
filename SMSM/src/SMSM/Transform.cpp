#include <SMSM/Transform.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>


SMSM_NAMESPACE_ENTER
{
	Transform::Transform() :
		scale(1, 1, 1)
	{

	}

	Matrix4 Transform::worldMatrix() const
	{
		return
			glm::translate(position) *
			glm::toMat4(rotation) *
			glm::scale(scale);
	}
}