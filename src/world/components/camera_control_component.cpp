#include "camera_control_component.h"
#include "world/gameobjects/camera.h"
#include "window/window_keys.h"
#include "world/gameobjects/world.h"
#include "transform_component.h"
#include "common/log.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(CameraControlComponent, Camera)

		CameraControlComponent::CameraControlComponent(Camera * camera): BaseComponent(camera), camera(camera)
		{
		}
		CameraControlComponent::~CameraControlComponent()
		{
			camera = nullptr;
		}
		void CameraControlComponent::update_camera()
		{
			update_move_dir();
			update_rotation();
			// update center, forward, up
			auto delta = m_move_dir * m_move_speed;
			auto comp = GET_COMPONENT(camera, TransformComponent);
			if (!comp)
			{
				log_warn("[Camera]Transform component is required, but it is not existed");
				return;
			}
			auto rot_mtx = math3d::Matrix::makeRotationMatrix(m_rotation);
			comp->rotation = rot_mtx;
			auto tmp = rot_mtx * math3d::Vector4(delta.x, delta.y, delta.z, 1);
			comp->position += math3d::Vector3(tmp.x, tmp.y, tmp.z);
		}
		void CameraControlComponent::update_move_dir()
		{
			auto win = World::get_instance()->get_window();
			if (!win) return;
			auto func = [&win](int key_f, int key_b)->float
			{
				auto state_w = win->get_key_state(key_f);
				auto state_s = win->get_key_state(key_b);
				if (state_w == WATER_PRESS || state_w == WATER_REPEAT)
				{
					return 1;
				}
				else if (state_s == WATER_PRESS || state_s == WATER_REPEAT)
				{
					return -1;
				}
				else
				{
					return 0;
				}
			};
			m_move_dir.z = func(WATER_KEY_S, WATER_KEY_W);	// z is in negtive direction
			m_move_dir.x = func(WATER_KEY_D, WATER_KEY_A);
			m_move_dir.y = func(WATER_KEY_LEFT_SHIFT, WATER_KEY_LEFT_CONTROL);

		}
		void CameraControlComponent::update_rotation()
		{
			auto win = World::get_instance()->get_window();
			if (!win) return;
			auto pre_pos = m_cursor_pos;
			m_cursor_pos = win->get_cursor_position();
			auto mouse_state = win->get_mouse_state(WATER_MOUSE_BUTTON_LEFT);
			if (mouse_state != WATER_PRESS)
			{
				return;
			}
			auto delta_pos = m_cursor_pos - pre_pos;
			auto win_size = win->get_window_size();

			auto speed = m_rotation_speed / win_size.x;

			m_rotation.y += -delta_pos.x * speed;	// yaw
			m_rotation.x += -delta_pos.y * speed;		// pitch
		}
	}
}