#ifndef WATER_CAMERA_H
#define WATER_CAMERA_H

#include "math3d/math3d.hpp"
#include <memory>
#include "space_object.h"

namespace water
{
	namespace world
	{
		class Camera: public SpaceObject
		{
		public:
			// Constructors
			using SpaceObject::SpaceObject;
			using SpaceObject::operator=;
		public:
			// get view matrix
			math3d::Matrix get_view_matrix();
			// get projection matrix
			math3d::Matrix get_projection_matrix();

		public:
			float fovy = { 50 };
			float aspect = { 1 };
			float z_near = { 1 };
			float z_far = { 1000 };
		};

		DECL_SHARED_PTR(Camera);
		DECL_WEEK_PTR(Camera);
	}
}

#endif // !WATER_CAMERA_H
