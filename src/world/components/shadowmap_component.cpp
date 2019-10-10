#include "shadowmap_component.h"
#include "render/device.h"
#include "world/gameobjects/world.h"
#include "mesh_component.h"
#include "render/material.h"
#include "material_component.h"
#include "render/render_task.h"

namespace water {
	namespace world
	{
		REGISTER_COMPONENT(ShadowMapComponent, SpaceObject);

		ShadowMapComponent::ShadowMapComponent(SpaceObject * space_object): BaseComponent(space_object)
		{

		}

		ShadowMapComponent & ShadowMapComponent::operator=(const ShadowMapComponent & trans_comp)
		{
			if (this == &trans_comp)
			{
				return *this;
			}
			BaseComponent::operator=(trans_comp);
			m_material = trans_comp.m_material;
			return *this;
		}

		void ShadowMapComponent::render()
		{
			auto device = render::get_device();
			auto window = World::get_instance()->get_window();
			if (m_render_target_ptr == nullptr)
			{
				auto size = window->get_window_size();
				m_render_target_ptr = device->create_render_target(size.x, size.y);
				m_render_target_ptr->init_attachments({ render::ATTACHMENT_DEPTH }, {});
			}
			render::RenderTaskPtr task = std::make_shared<render::RenderTargetTask>(render::RenderTargetTask::CMD_BIND_FOR_WIRTE, m_render_target_ptr);
			render::RenderTaskManager::get_instance()->add_task(task);
			// start draw task
			render::DrawCommand draw_cmd;
			MaterialComponent::update_material(m_game_object, m_material);
			auto render_comp = GET_COMPONENT(m_game_object, RenderComponent);
			render_comp->render(draw_cmd, m_material);
			// end draw task
			task = std::make_shared<render::RenderTargetTask>(render::RenderTargetTask::CMD_RESET, m_render_target_ptr);
			render::RenderTaskManager::get_instance()->add_task(task);
		}

		render::TexturePtr ShadowMapComponent::get_shadow_map()
		{
			return m_render_target_ptr->get_texture(render::ATTACHMENT_DEPTH);
		}
		void ShadowMapComponent::init(const std::string & mat_path)
		{
			m_material = std::make_shared<render::Material>();
			m_material->load_from_file(mat_path);
		}
	}
}