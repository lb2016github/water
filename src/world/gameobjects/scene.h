#ifndef WATER_SCENE_H
#define WATER_SCENE_H
#include "camera.h"
#include <set>
#include "render/draw_command.h"
#include "common/common.h"

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

			//load scene from file
			void load_from_file(std::string filepath);

			// tick
			void tick(unsigned int delta_time);
		protected:
			virtual std::set<ComponentTag> get_comp_tags();
		protected:
			// current camera
			CameraPtr m_cur_camera;
			render::DrawCommand draw_cmd = { render::TRIANGLES };
		};

		DECL_SHARED_PTR(Scene);
		DECL_WEEK_PTR(Scene);
	}
}

#endif // !WATER_SCENE_H
