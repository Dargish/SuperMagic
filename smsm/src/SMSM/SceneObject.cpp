#include <SMSM/SceneObject.h>

SMSM_NAMESPACE_ENTER
{
	Transform& SceneObject::transform()
	{
		return m_transform;
	}
	const Transform& SceneObject::transform() const
	{
		return m_transform;
	}
}