#pragma once

#include <SMSM/Transform.h>

SMSM_NAMESPACE_ENTER
{
	class SMSMAPI SceneObject
	{
	public:
		Transform& transform();
		const Transform& transform() const;

	private:
		Transform m_transform;
	};
}