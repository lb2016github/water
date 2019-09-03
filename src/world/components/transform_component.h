#ifndef WATER_TRANSFORM_COMPONENT_H
#define WATER_TRANSFORM_COMPONENT_H
#include "base_component.h"
#include "math3d/math3d.hpp"
#include "world/gameobjects/space_object.h"

namespace water {
	namespace world
	{
		class TransformComponent : public BaseComponent
		{
		public:
			TransformComponent(SpaceObject* space_object);
			virtual TransformComponent& operator = (const TransformComponent& trans_comp);

		public:
			math3d::Matrix get_world_transformation();
			math3d::Matrix get_transformation();
		public:
			math3d::Vector3 position = { 0, 0, 0 };
			math3d::Vector3 rotation = { 0, 0, 0 };
			math3d::Vector3 scale = { 1, 1, 1 };
		};
	}
}

// todo register component

#endif
