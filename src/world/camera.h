#ifndef WATER_CAMERA_H
#define WATER_CAMERA_H

#include "gameobjects/game_object.h"
#include "math3d/math3d.hpp"
#include <memory>

namespace water
{
	namespace world
	{
		class Camera: public GameObject
		{
		public:
			Camera();
			Camera(const Camera& camera);
			Camera& operator = (const Camera& camera);
			virtual ~Camera();

		public:
			// get view matrix
			math3d::Matrix get_view_matrix();
		};

		typedef std::shared_ptr<Camera> CameraPtr;
	}
}

#endif // !WATER_CAMERA_H
