#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "world/components/component.h"
#include "world/components/component_const.h"
#include <map>
#include <string>

namespace water {
	namespace world
	{
		typedef std::map<ComponentTag, Component*> COMPONENT_MAP;

		class GameObject {
		public:
			GameObject();
			GameObject(const GameObject& game_object);
			GameObject& operator = (const GameObject& game_object);
			virtual ~GameObject();

			Component* get_component(ComponentTag comp);

		protected:
			Component* add_component(ComponentTag comp);

		public:
			GameObject * m_parent;		// parent
		private:
			COMPONENT_MAP m_components;
		};
	}
}
#endif
