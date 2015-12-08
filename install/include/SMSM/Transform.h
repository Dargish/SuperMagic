#pragma once

#include <SMSM/SMSM.h>


SMSM_NAMESPACE_ENTER
{
	struct SMSMAPI Transform
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform();

		Matrix4 worldMatrix() const;
	};
}