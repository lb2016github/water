#include "scene.h"

namespace water
{
	namespace world
	{
		CameraPtr Scene::get_active_camera()
		{
			return m_cur_camera;
		}
		void Scene::set_active_camera(CameraPtr cam_ptr)
		{
			m_cur_camera = cam_ptr;
		}
	}
}
