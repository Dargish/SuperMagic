#include <SMSM/Component.h>

SMSM_NAMESPACE_ENTER
{
	Component::~Component()
	{

	}

	void Component::update(float /*deltaTime*/)
	{

	}

	SceneObject& Component::sceneObject()
	{
		return *m_sceneObject;
	}

	const SceneObject& Component::sceneObject() const
	{
		return *m_sceneObject;
	}
}