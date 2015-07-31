#pragma once

#include <SMSM/SMSM.h>
#include <SMSM/Transform.h>
#include <SMSM/Component.h>
#include <SMSM/ptr_vector.h>

#include <map>


SMSM_NAMESPACE_ENTER
{
	typedef ptr_vector<Component> Components;

	class SMSMAPI SceneObject
	{
	public:
		Transform& transform();
		const Transform& transform() const;

		void update(float deltaTime);

		template<typename COMPONENT_TYPE>
		COMPONENT_TYPE& createComponent();

		template<typename COMPONENT_TYPE>
		Components::iterator_range components();

		template<typename COMPONENT_TYPE>
		Components::const_iterator_range components() const;

	private:
		Transform m_transform;

		typedef std::map<std::string, Components> ComponentMap;
		ComponentMap m_componentMap;
	};

	template<typename COMPONENT_TYPE>
	COMPONENT_TYPE& SceneObject::createComponent()
	{
		Components& vec = m_componentMap[COMPONENT_TYPE::TYPE_NAME];
		COMPONENT_TYPE* component = new COMPONENT_TYPE;
		component->m_sceneObject = this;
		vec.push_back(component);
		return vec.back().as<COMPONENT_TYPE>();
	}

	template<typename COMPONENT_TYPE>
	Components::iterator_range SceneObject::components()
	{
		ComponentMap::iterator found = m_componentMap.find(COMPONENT_TYPE::TYPE_NAME);
		if (found != m_componentMap.end())
		{
			return found->second.range();
		}
		return Components::iterator_range();
	}

	template<typename COMPONENT_TYPE>
	Components::const_iterator_range SceneObject::components() const
	{
		ComponentMap::const_iterator found = m_componentMap.find(COMPONENT_TYPE::TYPE_NAME);
		if (found != m_componentMap.end())
		{
			return found->second.range();
		}
		return Components::const_iterator_range();
	}
}