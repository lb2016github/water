#ifndef WATER_CAEMRA_CONTROL_COMPONENT_H
#define WATER_CAEMRA_CONTROL_COMPONENT_H
#include "base_component.h"

namespace water
{
	namespace world
	{
		class Camera;

		class CameraControlComponent : public BaseComponent
		{
		public:
			CameraControlComponent(Camera* camera);
			using BaseComponent::operator=;
			virtual ~CameraControlComponent();
			static const ComponentTag tag = COMP_CAMERA_CONTROLLER;
		public:
			void update_camera();
			// update move of camera
			void update_move_dir();


		private:
			Camera* camera = { nullptr };
			math3d::Vector3 m_move_dir = { 0, 0, 0 };	// right, up, forward
			float m_speed = 0.01;
		};

	}
}

#endif // !WATER_CAEMRA_CONTROL_COMPONENT_H
