#include "world/gameobjects/game_object.h"

namespace water {
	namespace world
	{
		GameObject::GameObject()
		{
			auto tags = get_comp_tags();
			for each (auto tag in tags)
			{
				add_component(tag);
			}
		}

		GameObject::GameObject(const GameObject& game_object)
		{
			// copy components
			for (COMPONENT_MAP::const_iterator iter = game_object.m_components.begin(); iter != game_object.m_components.end(); ++iter)
			{
				BaseComponent* comp = add_component(iter->first);
				if (comp) {
					*comp = *(iter->second);
				}
			}
		}

		GameObject& GameObject::operator=(const GameObject& game_object)
		{
			if (this == &game_object) {
				return *this;
			}
			// copy components
			for (COMPONENT_MAP::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
			{
				COMPONENT_MAP::const_iterator find_iter = game_object.m_components.find(iter->first);
				if (find_iter != game_object.m_components.end())
				{
					*(iter->second) = *(find_iter->second);
				}
			}
			return *this;
		}

		GameObject::~GameObject()
		{
			for (COMPONENT_MAP::iterator iter = m_components.begin(); iter != m_components.end(); ++iter) {
				delete iter->second;
			}
			m_components.clear();
		}

		BaseComponent* GameObject::get_component(ComponentTag comp)
		{
			COMPONENT_MAP::iterator iter = m_components.find(comp);
			if (iter == m_components.end()) {
				return NULL;
			}
			return iter->second;
		}

		BaseComponent* GameObject::add_component(ComponentTag comp_tag)
		{
			auto rst = m_components.find(comp_tag);
			if (rst != m_components.end()) {
				return rst->second;
			}
			
			BaseComponent* comp = create_component(comp_tag, this);
			m_components[comp_tag] = comp;
			return comp;
		}
		std::set<ComponentTag> GameObject::get_comp_tags()
		{
			return std::set<ComponentTag>();
		}
	}
}