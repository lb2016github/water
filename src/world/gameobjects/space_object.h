#ifndef WATER_SPACE_OBJECT_H
#define WATER_SPACE_OBJECT_H

#include "game_object.h"

namespace water
{
	namespace world
	{
		class SpaceObject : public GameObject
		{
		public:
			using GameObject::GameObject;

			SpaceObject(SpaceObject* parent);
			virtual ~SpaceObject();

			SpaceObject& operator = (const SpaceObject& game_object);

			void set_parent(SpaceObject* space_object);
			inline SpaceObject* get_parent();

		protected:
			virtual std::set<ComponentTag> get_comp_tags();
		protected:
			SpaceObject * m_parent{ nullptr };		// parent
		};
	}
}

#endif // !WATER_SPACE_OBJECT_H
