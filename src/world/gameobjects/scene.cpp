#include "scene.h"
#include "world/components/render_component.h"

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
		void Scene::render(const render::DrawCommand & draw_cmd)
		{
			for each (SpaceObjectPtr obj_ptr in m_children)
			{
				auto render_comp = GET_COMPONENT(obj_ptr, RenderComponent);
				if (!render_comp) continue;
				render_comp->render(draw_cmd);
			}
		}
	}
}
