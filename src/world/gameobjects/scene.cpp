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
			auto render_comp = GET_COMPONENT(this, RenderComponent);
			render_comp->render(draw_cmd);
		}
		std::set<ComponentTag> Scene::get_comp_tags()
		{
			auto rst = SpaceObject::get_comp_tags();
			rst.insert(RenderComponent::tag);
			return rst;
		}
	}
}
