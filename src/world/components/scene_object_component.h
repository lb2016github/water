#ifndef WATER_SCENE_OBJECT_COMPONENT_H
#define WATER_SCENE_OBJECT_COMPONENT_H

#include "base_component.h"
#include "world/gameobjects/space_object.h"
#include "world/gameobjects/scene.h"

namespace water
{
	namespace world
	{
		class SceneObjectComponent : public BaseComponent
		{
		public:
			SceneObjectComponent(SpaceObject* space_object);
			virtual SceneObjectComponent& operator = (const SceneObjectComponent& scene_comp);

			static const ComponentTag tag = COMP_TRANSFORMATION;

		public:
			ScenePtr get_scene();
			void on_add_to_scene(ScenePtr scene);
			void on_remove_from_scene();

		private:
			SceneWeekPtr m_scene;
		};

	}
}

#endif // !WATER_SCENE_OBJECT_COMPONENT_H
