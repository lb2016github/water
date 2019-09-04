#ifndef WATER_BASE_COMPONENT_H
#define WATER_BASE_COMPONENT_H

#include "math3d/math3d.hpp"
#include <string>
#include <map>
#include "component_const.h"
#include <functional>

#define REGISTER_COMPONENT(cls, obj_type)\
water::world::BaseComponent* create_##comp_tag(void* obj)\
{\
	return new cls((obj_type*)obj);\
}\
water::world::ComponentInfo comp(cls::tag, create_##comp_tag);


namespace water {
	namespace world
	{
		class GameObject;

		class BaseComponent {
		public:
			BaseComponent(GameObject* game_object);
			BaseComponent(const BaseComponent& comp) = delete;	// copy contructor is not allowed in void of to game object has two same component
			virtual BaseComponent& operator = (const BaseComponent& comp);
			virtual ~BaseComponent();

			static const ComponentTag tag;

		protected:
			GameObject * m_game_object;
		};

		typedef std::function<BaseComponent* (void*)> FUNC_CREATE_COMPONENT;
		struct ComponentInfo
		{
			ComponentInfo(ComponentTag comp_tag, FUNC_CREATE_COMPONENT func_create);
		};

		BaseComponent* create_component(ComponentTag tag, GameObject* obj);
	}
}
#endif
