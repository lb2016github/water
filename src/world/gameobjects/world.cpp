#include "world.h"

namespace water
{
	namespace world
	{
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
		World * World::get_instance()
		{
			if (World::instance == nullptr)
			{
				instance = new World();
			}
			return instance;
		}
		World::World(): GameObject()
		{
		}
		std::set<ComponentTag> World::get_comp_tags()
		{
			// todo
			return std::set<ComponentTag>();
		}
	}
}