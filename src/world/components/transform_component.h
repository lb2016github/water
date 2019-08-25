#ifndef WATER_TRANSFORM_COMPONENT_H
#define WATER_TRANSFORM_COMPONENT_H
#include "component.h"
#include "math3d/math3d.hpp"

namespace water {
	namespace world
	{
		class TransformComponent : public Component {
		public:
			TransformComponent();
			TransformComponent(GameObject* game_object);
			TransformComponent(const TransformComponent& trans_comp);
			TransformComponent& operator = (const TransformComponent& trans_comp);

			math3d::Matrix get_world_transformation();

		public:
			math3d::Matrix transformation;
		};
	}
}

// todo register component

#endif
