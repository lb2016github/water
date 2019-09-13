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
			// update center, forward, up
			auto delta = m_move_dir * m_speed;
			auto comp = GET_COMPONENT(camera, TransformComponent);
			if (!comp)
			{
				log_warn("[Camera]Transform component is required, but it is not existed");
				return;
			}
			comp->position += delta;
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
	}
}