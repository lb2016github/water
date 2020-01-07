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
			// update dir of camera
			void update_rotation();


		private:
			Camera* camera = { nullptr };
			math3d::EulerAngle m_rotation = { 0, 0, 0 };	// pitch yaw roll
			math3d::Vector2 m_cursor_pos;	// save pre cursor pos
			math3d::Vector3 m_move_dir = { 0, 0, 0 };
			// move speed
			float m_move_speed = 0.01;
			// defines rotation angle when mouse move from left edge to right edge
			// note that angle is represented by radian
			float m_rotation_speed{ 3.14f };
		};

	}
}

#endif // !WATER_CAEMRA_CONTROL_COMPONENT_H
