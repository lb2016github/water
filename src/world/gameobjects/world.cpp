#include "world.h"
#include "scene.h"
#include "render/render_task.h"

namespace water
{
	namespace world
	{
		World* world_ptr = nullptr;
		ScenePtr World::get_cur_scene()
		{
			return m_cur_scene;
		}
		void World::set_cur_scene(ScenePtr scene)
		{
			m_cur_scene = scene;
			// add to scene set
			auto rst = m_scene_set.find(scene);
			if (rst == m_scene_set.end())
			{
				m_scene_set.insert(scene);
			}
		}
		void World::remove_scene(ScenePtr scene)
		{
			auto rst = m_scene_set.find(scene);
			if (rst != m_scene_set.end())
			{
				m_scene_set.erase(scene);
			}
			if (m_cur_scene == scene)
			{
				m_cur_scene = nullptr;
			}
			return;
		}
		ScenePtr World::load_scene(const std::string& scene_path)
		{
			auto scn_ptr = std::make_shared<Scene>();
			scn_ptr->load_from_file(scene_path);
			m_scene_set.insert(scn_ptr);
			return scn_ptr;
		}
		void World::on_frame()
		{
			if (m_cur_scene)
			{
				m_cur_scene->on_frame();
			}
			render::RenderTaskManager::get_instance()->tick();

		}
		World * World::get_instance()
		{
			if (world_ptr == nullptr)
			{
				world_ptr = new World();
			}
			return world_ptr;
		}
		World::World()
		{
		}
	}
}