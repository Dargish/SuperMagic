#pragma once

#include <SMRT/SMRT.h>
#include <SMRT/SceneObject.h>

#include <vector>

SMRT_NAMESPACE_ENTER
{
	typedef std::vector<SceneObject> SceneObjects;

	class Scene
	{
	public:
		typedef SceneObjects::size_type size_type;
		typedef SceneObjects::iterator iterator;
		typedef SceneObjects::const_iterator const_iterator;

		Scene();

		void push_back(const SceneObject& sceneObject);

		size_type size();

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

	private:
		SceneObjects m_sceneObjects;
	};
}