#ifndef WATER_GAME_OBJECT_H
#define WATER_GAME_OBJECT_H

#include "world/components/base_component.h"
#include "world/components/component_const.h"
#include <map>
#include <string>
#include <set>

#define GET_COMPONENT(obj_ptr, cls) (cls*)obj_ptr->get_component(cls::tag);

namespace water {
	namespace world
	{
		typedef std::map<ComponentTag, BaseComponent*> COMPONENT_MAP;

		class GameObject {
		public:
			GameObject();
			GameObject(const GameObject& game_object);
			GameObject& operator = (const GameObject& game_object);
			virtual ~GameObject();

			BaseComponent* get_component(ComponentTag comp);

		protected:
			BaseComponent* add_component(ComponentTag comp);
			virtual std::set<ComponentTag> get_comp_tags() = 0;

		private:
			COMPONENT_MAP m_components;
		};
	}
}
#endif
