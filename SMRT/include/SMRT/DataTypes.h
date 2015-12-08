#pragma once

#include <SMRT/SMRT.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

SMRT_NAMESPACE_ENTER
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef glm::mat4 Matrix4;
	typedef glm::quat Quaternion;
	typedef glm::vec3 Vector3;
}

#include <SMRT/DataTypes/Ray.h>
#include <SMRT/DataTypes/RGBA.h>
#include <SMRT/DataTypes/Transform.h>
