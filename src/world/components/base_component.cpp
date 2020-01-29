#include "base_component.h"

namespace water
{
	namespace world
	{
		std::map<ComponentTag, FUNC_CREATE_COMPONENT> comp_map;

		BaseComponent::~BaseComponent()
		{
			m_game_object = nullptr;
		}

		BaseComponent& BaseComponent::operator=(const BaseComponent& comp)
		{
			if (&comp == this) {
				return *this;
			}
			m_tickEnable = comp.m_tickEnable;
			return *this;
		}

		BaseComponent::BaseComponent(GameObject* game_object): m_game_object(game_object), ITickable(true)
		{
			assert(game_object != nullptr);
		}
		ComponentInfo::ComponentInfo(ComponentTag comp_tag, FUNC_CREATE_COMPONENT func_create)
		{
			comp_map[comp_tag] = func_create;
		}
		BaseComponent* create_component(ComponentTag tag, GameObject* obj)
		{
			auto rst = comp_map.find(tag);
			if (rst == comp_map.end()) return nullptr;
			return rst->second(obj);
		}
	}
}

