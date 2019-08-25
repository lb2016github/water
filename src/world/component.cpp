#include "world/component.h"

namespace water
{
	namespace world
	{
		void ComponentFactory::register_component(std::string comp_name, FUNC_CREATE_COMPONENT create_func)
		{
			assert(m_creaters.find(comp_name) == m_creaters.end());
			m_creaters[comp_name] = create_func;
		}

		Component* ComponentFactory::create_component(std::string comp_name, GameObject* game_object)
		{
			assert(m_creaters.find(comp_name) == m_creaters.end());
			FUNC_CREATE_COMPONENT create_func = m_creaters[comp_name];
			return create_func(game_object);
		}

		ComponentFactory* ComponentFactory::instance() {
			return &ComponentFactory::m_instance;
		}

		Component::Component(): Component(NULL, NULL)
		{

		}

		Component::Component(const Component& comp, GameObject* game_object): m_game_object(game_object)
		{
			
		}

		Component::~Component()
		{
			m_game_object = NULL;
		}

		GameObject* Component::get_game_object()
		{
			return m_game_object;
		}

		void Component::set_game_object(GameObject* game_object)
		{
			m_game_object = game_object;
		}

		Component& Component::operator=(const Component& comp)
		{
			if (&comp == this) {
				return *this;
			}
			//m_game_object = comp.m_game_object;
			return *this;
		}

		Component::Component(const Component& comp)
		{
			
		}

		Component::Component(GameObject* game_object): m_game_object(game_object)
		{
			
		}
		
	}
}

