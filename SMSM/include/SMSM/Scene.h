#pragma once

#include <SMSM/SMSM.h>
#include <SMSM/SceneObject.h>
#include <SMSM/ptr_vector.h>

SMSM_NAMESPACE_ENTER
{
	typedef ptr_vector<SceneObject> SceneObjects;
	
	class SMSMAPI Scene
	{
	public:
		Scene();

		SceneObject& createSceneObject();

		void update(float deltaTime);

		SceneObjects::iterator begin();
		SceneObjects::const_iterator begin() const;

		SceneObjects::iterator end();
		SceneObjects::const_iterator end() const;

	private:
		SceneObjects m_sceneObjects;
	};
}