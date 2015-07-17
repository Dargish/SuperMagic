#pragma once

#include <SMSM/SMSM.h>


SMSM_NAMESPACE_ENTER
{
	class SMSMAPI Transform
	{
	public:
		Transform();
		
		Vector3& position();
		const Vector3& position() const;

		Quaternion& rotation();
		const Quaternion& rotation() const;

		Vector3& scale();
		const Vector3& scale() const;

		void setWorldMatrix(Matrix4& worldMatrix);

	private:
		Vector3 m_position;
		Quaternion m_rotation;
		Vector3 m_scale;
	};
}