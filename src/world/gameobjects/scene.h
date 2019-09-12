#ifndef WATER_SCENE_H
#define WATER_SCENE_H
#include "camera.h"
#include <set>
#include "render/draw_command.h"
#include "common/common.h"
#include "world/components/render_component.h"
#include "space_object.h"

namespace water
{
	namespace world
	{
		class Scene: public SpaceObject, public ComponentObject<RenderComponent>
		{
		public:
			CameraPtr get_active_camera();
			void set_active_camera(CameraPtr cam_ptr);
			void render(const render::DrawCommand& draw_cmd);

			//load scene from file
			void load_from_file(std::string filepath);

			// tick
			void on_frame();

		protected:
			// current camera
			CameraPtr m_cur_camera;
			render::DrawCommand draw_cmd;
		};

		DECL_SHARED_PTR(Scene);
		DECL_WEEK_PTR(Scene);
	}
}

#endif // !WATER_SCENE_H
