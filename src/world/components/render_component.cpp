#include "render_component.h"
#include "mesh_component.h"
#include "material_component.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(RenderComponent, SpaceObject);

		RenderComponent::RenderComponent(SpaceObject * space_object): BaseComponent(space_object), m_space_object(space_object)
		{
		}

		void RenderComponent::render(const render::DrawCommand & draw_cmd)
		{
			for each (auto obj in m_space_object->get_children())
			{
				auto render_comp = GET_COMPONENT(obj, RenderComponent);
				if (render_comp)
				{
					render_comp->render(draw_cmd);
				}
			}

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
		}
		void RenderComponent::render(const render::DrawCommand & draw_cmd, render::MaterialPtr mat_ptr)
		{
			for each (auto obj in m_space_object->get_children())
			{
				auto render_comp = GET_COMPONENT(obj, RenderComponent);
				if (render_comp)
				{
					render_comp->render(draw_cmd, mat_ptr);
				}
			}

			auto mesh_comp = GET_COMPONENT(m_game_object, MeshComponent);
			if (!mesh_comp) return;
			auto mesh_ptr = mesh_comp->get_mesh_ptr();
			if (!mesh_ptr) return;
			MaterialComponent::update_material(m_game_object, mat_ptr);
			mat_ptr->render(draw_cmd, mesh_ptr);
		}
	}
}