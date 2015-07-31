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

	void SceneObject::update(float deltaTime)
	{
		for(ComponentMap::iterator it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
		{
			Components& vec = it->second;
			for(Components::iterator cit = vec.begin(); cit != vec.end(); ++cit)
			{
				cit->update(deltaTime);
			}
		}
	}
}