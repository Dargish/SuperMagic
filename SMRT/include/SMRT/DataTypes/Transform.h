#pragma once

#include <SMRT/SMRT.h>


SMRT_NAMESPACE_ENTER
{
	struct Transform
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform();

		Matrix4 worldMatrix() const;
	};
}