#pragma once

#include <SMSM/SMSM.h>

SMSM_NAMESPACE_ENTER
{
	class SceneObject;

	struct SMSMAPI Component
	{
		SMSM_TYPENAME(Component);

		virtual ~Component();

		virtual void update(float /*deltaTime*/);

		template<typename U>
		U& as();

		template<typename U>
		const U& as() const;

		SceneObject& sceneObject();
		const SceneObject& sceneObject() const;

	private:
		friend class SceneObject;
		SceneObject* m_sceneObject;
	};

	template<typename U>
	U& Component::as()
	{
		return *(dynamic_cast<U*>(this));
	}

	template<typename U>
	const U& Component::as() const
	{
		return *(dynamic_cast<const U*>(this));
	}
}