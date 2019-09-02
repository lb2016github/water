#include "material_component.h"
#include "render/material.h"
#include "common/log.h"

namespace water
{
	namespace world
	{

		Component* MaterialComponent::create_component(GameObject* gameobject)
		{
			return new MaterialComponent(gameobject);
		}

		bool MaterialComponent::has_param(std::string name, unsigned int index)
		{
			auto ptr = m_material_ptr->get_param_map(index);
			if (!ptr) return false;
			return ptr->has_param(name);
		}

		void MaterialComponent::render(const render::DrawCommand& draw_cmd, render::MeshDataPtr mesh_ptr)
		{
			if (!m_material_ptr)
			{
				log_warn("[RENDER]No material is inited\n");
				return;
			}
			// do something before rendering
			before_render();
			m_material_ptr->render(draw_cmd, mesh_ptr);
		}

		render::MaterialPtr MaterialComponent::get_material()
		{
			return m_material_ptr;
		}

		void MaterialComponent::load_from_file(const std::string& filepath)
		{
			m_material_ptr->load(filepath.c_str());
		}

		void MaterialComponent::before_render()
		{
			// todo set materials
		}

		ComponentTag MaterialComponent::tag = COMP_MATERIAL;

		ComponentInfo comp_info(MaterialComponent::tag, MaterialComponent::create_component);

		MaterialComponent::MaterialComponent(GameObject * game_object): Component(game_object)
		{
			m_material_ptr = std::make_shared<render::Material>();
		}
		MaterialComponent::MaterialComponent(const MaterialComponent & comp, GameObject * game_object):
			MaterialComponent(game_object)
		{
			m_material_ptr = comp.m_material_ptr;
		}
		MaterialComponent & MaterialComponent::operator=(const MaterialComponent & comp)
		{
			if (this == &comp) return *this;
			Component::operator=(comp);
			m_material_ptr = comp.m_material_ptr;
			return *this;
		}
		MaterialComponent::~MaterialComponent()
		{
			m_material_ptr = nullptr;
		}
	}
}

