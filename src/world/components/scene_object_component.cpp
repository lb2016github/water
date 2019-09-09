#include "scene_object_component.h"
#include "world/gameobjects/space_object.h"
#include "world/gameobjects/scene.h"


namespace water
{
	namespace world
	{
		REGISTER_COMPONENT(SceneObjectComponent, SpaceObject);

		SceneObjectComponent::SceneObjectComponent(SpaceObject* space_object): BaseComponent(space_object)
		{
		}
		SceneObjectComponent& SceneObjectComponent::operator=(const SceneObjectComponent& scene_comp)
		{
			if (this == &scene_comp) return *this;
			BaseComponent::operator=(scene_comp);

			return *this;
		}
		ScenePtr SceneObjectComponent::get_scene()
		{
			return m_scene.lock();
		}
		void SceneObjectComponent::on_add_to_scene(ScenePtr scene)
		{
			m_scene = scene;
		}
		void SceneObjectComponent::on_remove_from_scene()
		{
			m_scene.reset();
		}
	}
}