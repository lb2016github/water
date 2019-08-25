#include "world/gameobjects/game_object.h"

namespace water {
	namespace world
	{
		GameObject::GameObject(): m_parent(NULL)
		{

		}

		GameObject::GameObject(const GameObject& game_object): m_parent(game_object.m_parent)
		{
			// copy components
			for (COMPONENT_MAP::const_iterator iter = game_object.m_components.begin(); iter != game_object.m_components.end(); ++iter)
			{
				Component* comp = add_component(iter->first);
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
			m_parent = NULL;
		}

		Component* GameObject::get_component(ComponentTag comp)
		{
			COMPONENT_MAP::iterator iter = m_components.find(comp);
			if (iter == m_components.end()) {
				return NULL;
			}
			return iter->second;
		}

		Component* GameObject::add_component(ComponentTag comp_tag)
		{
			if (m_components.find(comp_tag) == m_components.end()) {
				return NULL;
			}
			Component* comp = ComponentFactory::instance()->create_component(comp_tag, this);
			m_components[comp_tag] = comp;
			return comp;
		}
	}
}