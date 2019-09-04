#ifndef WATER_SCENE_H
#define WATER_SCENE_H
#include "camera.h"
#include <set>
#include "render/draw_command.h"

namespace water
{
	namespace world
	{
		class Scene: public SpaceObject
		{
		public:
			using SpaceObject::SpaceObject;

			CameraPtr get_active_camera();
			void set_active_camera(CameraPtr cam_ptr);
			void render(const render::DrawCommand& draw_cmd);
		private:
			// current camera
			CameraPtr m_cur_camera;
			// children, todo save children to a new struct to speed up
			std::set<SpaceObjectPtr> m_children;
		};
	}
}

#endif // !WATER_SCENE_H
