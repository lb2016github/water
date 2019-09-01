#ifndef WATER_TRANSFORM_COMPONENT_H
#define WATER_TRANSFORM_COMPONENT_H
#include "component.h"
#include "math3d/math3d.hpp"

namespace water {
	namespace world
	{
		class TransformComponent : public Component
		{
		public:
			TransformComponent();
			TransformComponent(GameObject* game_object);
			TransformComponent(const TransformComponent& trans_comp);
			TransformComponent& operator = (const TransformComponent& trans_comp);

			// component info
			static ComponentTag tag;
			static Component* create_component(GameObject*);

		public:
			math3d::Matrix get_world_transformation();
			math3d::Matrix get_transformation();
		public:
			math3d::Vector3 position;
			math3d::Vector3 rotation;
			math3d::Vector3 scale;
		};
	}
}

// todo register component

#endif
