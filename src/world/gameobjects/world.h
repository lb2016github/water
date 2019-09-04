#ifndef WATER_WORLD_H
#define WATER_WORLD_H

#include "game_object.h"
#include "scene.h"

namespace water
{
	namespace world
	{
		class World: public GameObject
		{
		public:
			Scene* cur_scene;

		protected:
			World();
			World(const World& world) = delete;
			World& operator = (const GameObject& game_object) = delete;

			std::set<ComponentTag> get_comp_tags();
			
		};
	}
}

#endif // !WATER_WORLD_H
