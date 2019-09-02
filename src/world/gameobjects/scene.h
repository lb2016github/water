#ifndef WATER_SCENE_H
#define WATER_SCENE_H
#include "camera.h"

namespace water
{
	namespace world
	{
		class Scene: public GameObject
		{
			CameraPtr get_active_camera();
			void set_active_camera(CameraPtr cam_ptr);
		private:
			// current camera
			CameraPtr m_cur_camera;
			// children
			std::vector<GameObject> m_children;
		};
	}
}

#endif // !WATER_SCENE_H
