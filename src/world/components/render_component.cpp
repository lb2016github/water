#include "render_component.h"
#include "mesh_component.h"
#include "material_component.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(RenderComponent, GameObject);

		void RenderComponent::render(const render::DrawCommand & draw_cmd)
		{
			auto mesh_comp = GET_COMPONENT(m_game_object, MeshComponent);
			if (!mesh_comp) return;
			auto mesh_ptr = mesh_comp->get_mesh_ptr();
			if (!mesh_ptr) return;
			auto mat_comp = GET_COMPONENT(m_game_object, MaterialComponent);
			mat_comp->update_material();
			if (!mat_comp) return;
			auto mat_ptr = mat_comp->get_material();
			if (!mat_ptr) return;
			mat_ptr->render(draw_cmd, mesh_ptr);

			// todo render children
		}
		void RenderComponent::do_render(const render::DrawCommand & draw_cmd, GameObject * game_object)
		{
		}
	}
}