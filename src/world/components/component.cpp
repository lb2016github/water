#include "component.h"

namespace water
{
	namespace world
	{
		void ComponentFactory::register_component(ComponentTag comp, FUNC_CREATE_COMPONENT create_func)
		{
			assert(m_creaters.find(comp) == m_creaters.end());
			m_creaters[comp] = create_func;
		}

		Component* ComponentFactory::create_component(ComponentTag comp, GameObject* game_object)
		{
			assert(m_creaters.find(comp) == m_creaters.end());
			FUNC_CREATE_COMPONENT create_func = m_creaters[comp];
			return create_func(game_object);
		}

		ComponentFactory* ComponentFactory::instance() {
			return &ComponentFactory::m_instance;
		}

		Component::~Component()
		{
			m_game_object = nullptr;
		}

		GameObject* Component::get_game_object()
		{
			return m_game_object;
		}

		Component& Component::operator=(const Component& comp)
		{
			if (&comp == this) {
				return *this;
			}
			return *this;
		}

		Component::Component(GameObject* game_object): m_game_object(game_object)
		{
			assert(game_object != nullptr);
		}
		
		ComponentInfo::ComponentInfo(ComponentTag comp_tag, FUNC_CREATE_COMPONENT func_create)
		{
			ComponentFactory::instance()->register_component(comp_tag, func_create);
		}

	}
}

