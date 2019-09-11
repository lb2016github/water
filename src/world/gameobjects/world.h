#ifndef WATER_WORLD_H
#define WATER_WORLD_H

#include "game_object.h"
#include "scene.h"
#include <set>
#include "window/window_interface.h"
#include <string>

namespace water
{
	namespace world
	{
		class World: public IWindowCallback		{
		public:
			// scene methods
			ScenePtr get_cur_scene();
			void set_cur_scene(ScenePtr scene);
			void remove_scene(ScenePtr scene);
			ScenePtr load_scene(const std::string& scene_path);

			// on frame
			virtual void on_frame();

			static World* get_instance();

		protected:
			World();
			World(const World& world) = delete;
			World& operator = (const GameObject& game_object) = delete;

		protected:
			ScenePtr m_cur_scene;
			std::set<ScenePtr> m_scene_set;
		};
	}
}

#endif // !WATER_WORLD_H
