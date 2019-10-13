#ifndef WATER_TRANSFORM_COMPONENT_H
#define WATER_TRANSFORM_COMPONENT_H
#include "base_component.h"
#include "math3d/math3d.hpp"

namespace water {
	namespace world
	{
		class SpaceObject;

		class TransformComponent : public BaseComponent
		{
		public:
			TransformComponent(SpaceObject* space_object);
			virtual TransformComponent& operator = (const TransformComponent& trans_comp);

			static const ComponentTag tag = COMP_TRANSFORMATION;

		public:
			math3d::Matrix get_world_transformation();
			math3d::Matrix get_transformation();

			// position rotation scale
			void set_position(math3d::Vector3 pos);
			void set_position(std::string pos_str);
			void set_scale(math3d::Vector3 scale);
			void set_scale(std::string scale_str);
			void set_rotation(math3d::Vector3 rotation);
			void set_rotation(std::string rot_str);
		public:
			math3d::Vector3 position = { 0, 0, 0 };
			math3d::Vector3 scale = { 1, 1, 1 };
			math3d::Matrix rotation;
		};
	}
}

// todo register component

#endif
