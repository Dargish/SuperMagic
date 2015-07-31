#include <SMSM/Scene.h>

SMSM_NAMESPACE_ENTER
{
	Scene::Scene()
	{

	}

	SceneObject& Scene::createSceneObject()
	{
		m_sceneObjects.push_back(new SceneObject);
		return m_sceneObjects.back();
	}

	void Scene::update(float deltaTime)
	{
		for(SceneObjects::iterator it = begin(); it != end(); ++it)
		{
			it->update(deltaTime);
		}
	}

	SceneObjects::iterator Scene::begin()
	{
		return m_sceneObjects.begin();
	}

	SceneObjects::const_iterator Scene::begin() const
	{
		return m_sceneObjects.begin();
	}

	SceneObjects::iterator Scene::end()
	{
		return m_sceneObjects.end();
	}

	SceneObjects::const_iterator Scene::end() const
	{
		return m_sceneObjects.end();
	}
}