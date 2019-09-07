#ifndef WATER_WORLD_H
#define WATER_WORLD_H

#include "game_object.h"
#include "scene.h"
#include <set>

namespace water
{
	namespace world
	{
		class World: public GameObject
		{
		public:
			// scene methods
			ScenePtr get_cur_scene();
			void set_cur_scene(ScenePtr scene);
			void remove_scene(ScenePtr scene);


			static World* get_instance();

		protected:
			World();
			World(const World& world) = delete;
			World& operator = (const GameObject& game_object) = delete;
			
			static World* instance;

			std::set<ComponentTag> get_comp_tags();

		protected:
			ScenePtr m_cur_scene;
			std::set<ScenePtr> m_scene_set;
		};
	}
}

#endif // !WATER_WORLD_H
