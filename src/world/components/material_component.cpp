#include "material_component.h"
#include "render/material.h"
#include "common/log.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(COMP_MATERIAL, MaterialComponent, GameObject)

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
			if (!m_material_ptr)
			{
				auto num = m_material_ptr->get_param_map_count();
				for (int i = 0; i < num; ++i)
				{
					auto param_map = m_material_ptr->get_param_map(i);
					if (!param_map) continue;
					for (auto iter = param_map->m_semantic_map.begin(); iter != param_map->m_semantic_map.end(); ++i)
					{
						auto name = iter->first;
						auto sem = iter->second;
						// todo
					}
				}
			}
		}


		MaterialComponent::MaterialComponent(GameObject * game_object): BaseComponent(game_object)
		{
			m_material_ptr = std::make_shared<render::Material>();
		}
		MaterialComponent & MaterialComponent::operator=(const MaterialComponent & comp)
		{
			if (this == &comp) return *this;
			BaseComponent::operator=(comp);
			m_material_ptr = comp.m_material_ptr;
			return *this;
		}
		MaterialComponent::~MaterialComponent()
		{
			m_material_ptr = nullptr;
		}
	}
}

