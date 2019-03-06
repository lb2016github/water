#ifndef WATER_TRANSFORM_COMPONENT_H
#define WATER_TRANSFORM_COMPONENT_H
#include "world/component.h"
#include "math3d/math3d.hpp"

namespace water {
	class TransformComponent : public Component {
	public:
		TransformComponent();
		TransformComponent(GameObject* game_object);
		TransformComponent(const TransformComponent& trans_comp);
		TransformComponent& operator = (const TransformComponent& trans_comp);

		Matrix get_world_transformation();

	public:
		Matrix transformation;
	};
}

// todo register component

#endif
