#ifndef WATER_SCENE_OBJECT_COMPONENT_H
#define WATER_SCENE_OBJECT_COMPONENT_H

#include "base_component.h"
#include <memory>

namespace water
{
	namespace world
	{
		class SpaceObject;
		class Scene;

		class SceneObjectComponent : public BaseComponent
		{
		public:
			SceneObjectComponent(SpaceObject* space_object);
			virtual SceneObjectComponent& operator = (const SceneObjectComponent& scene_comp);

			static const ComponentTag tag = COMP_TRANSFORMATION;

		public:
			std::shared_ptr<Scene> get_scene();
			void on_add_to_scene(std::shared_ptr<Scene> scene);
			void on_remove_from_scene();

		private:
			std::weak_ptr<Scene> m_scene;
		};

	}
}

#endif // !WATER_SCENE_OBJECT_COMPONENT_H
