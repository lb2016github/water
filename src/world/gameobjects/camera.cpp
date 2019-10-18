#include "camera.h"
#include "world/components/transform_component.h"


namespace water
{
	namespace world
	{
		math3d::Matrix Camera::get_view_matrix()
		{
			auto comp = GET_COMPONENT(this, TransformComponent);
			math3d::Matrix mtx = comp->get_world_transformation();
			mtx = math3d::inverse(mtx);
			return mtx;
		}
		math3d::Matrix Camera::get_projection_matrix()
		{
			return math3d::get_perpective_matrix(z_near, z_far, fovy, aspect);
		}
		void Camera::update()
		{
			update_fovy();
			auto cam_trl_comp = GET_COMPONENT(this, CameraControlComponent);
			cam_trl_comp->update_camera();
		}
		void Camera::update_fovy()
		{
			auto window_ptr = WindowWin32::Instance();
			auto size = window_ptr->get_window_size();
			if (size.y <= 0.0001) return;
			aspect = size.x / size.y;
		}
	}
}
