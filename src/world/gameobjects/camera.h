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
			using SpaceObject::GameObject;
			using SpaceObject::SpaceObject;
			using SpaceObject::operator=;
		public:
			// get view matrix
			math3d::Matrix get_view_matrix();
		};

		typedef std::shared_ptr<Camera> CameraPtr;
	}
}

#endif // !WATER_CAMERA_H
