#ifndef WATER_WORLD_H
#define WATER_WORLD_H

#include "game_object.h"
#include "scene.h"
#include <set>
#include "window/window_interface.h"
#include <string>
#include "world/text/text.h"

namespace water
{
	namespace world
	{
		class World: public IWindowCallback		{
		public:
			// inherited methods
			void on_key_callback(int key, int action);
			// scene methods
			ScenePtr get_cur_scene();
			void set_cur_scene(ScenePtr scene);
			void remove_scene(ScenePtr scene);
			ScenePtr load_scene(const std::string& scene_path);

			// window
			void set_window(IWindow* win);
			IWindow* get_window();

			// on frame
			virtual void on_frame();

			static World* get_instance();

		public:
			TextManager m_text_mgr;

		protected:
			World();
			World(const World& world) = delete;
			World& operator = (const GameObject& game_object) = delete;

		protected:
			ScenePtr m_cur_scene;
			std::set<ScenePtr> m_scene_set;
			IWindow* m_window = { nullptr };
		};
	}
}

#endif // !WATER_WORLD_H
