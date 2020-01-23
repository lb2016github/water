#ifndef WATER_SCENE_H
#define WATER_SCENE_H
#include "camera.h"
#include <set>
#include "render/draw_command.h"
#include "common/common.h"
#include "world/components/render_component.h"
#include "space_object.h"
#include "render/light.h"
#include "billboardlist.h"
#include <vector>

namespace water
{
	namespace world
	{
		class Scene: public SpaceObject, public ComponentObject<RenderComponent>
		{
		public:
			// cameras
			CameraPtr get_active_camera();
			void set_active_camera(CameraPtr cam_ptr);
			// get light config
			render::LightConfig get_light_config();
			// get env map
			render::TexturePtr get_env_map();
			// render
			void render();

			//load scene from file
			void load_from_file(std::string filepath);

			// tick
			virtual void tick(float timeMic);

		protected:
			// light
			render::LightConfig m_light_cfg;
			// current camera
			CameraPtr m_cur_camera;
			// enable shadowmap
			bool enable_shadowmap = { true };
			// billboardlist
			std::vector<BillboardListPtr> m_billboards;
			// env texture
			render::TexturePtr m_env;
		};

		DECL_SHARED_PTR(Scene);
		DECL_WEEK_PTR(Scene);
	}
}

#endif // !WATER_SCENE_H
