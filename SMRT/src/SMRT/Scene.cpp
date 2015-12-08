#include <SMRT/Scene.h>

SMRT_NAMESPACE_ENTER
{
	Scene::Scene()
	{

	}

	void Scene::push_back(const SceneObject& sceneObject)
	{
		m_sceneObjects.push_back(sceneObject);
	}

	Scene::size_type Scene::size()
	{
		return m_sceneObjects.size();
	}

	Scene::iterator Scene::begin()
	{
		return m_sceneObjects.begin();
	}

	Scene::const_iterator Scene::begin() const
	{
		return m_sceneObjects.begin();
	}

	Scene::iterator Scene::end()
	{
		return m_sceneObjects.end();
	}

	Scene::const_iterator Scene::end() const
	{
		return m_sceneObjects.end();
	}
}