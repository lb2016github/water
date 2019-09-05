#include "material_component.h"
#include "render/material.h"
#include "common/log.h"
#include "transform_component.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(MaterialComponent, GameObject)

		bool MaterialComponent::has_param(std::string name, unsigned int index)
		{
			auto ptr = m_material_ptr->get_param_map(index);
			if (!ptr) return false;
			return ptr->has_param(name);
		}

		render::MaterialPtr MaterialComponent::get_material()
		{
			return m_material_ptr;
		}

		void MaterialComponent::load_from_file(const std::string& filepath)
		{
			m_material_ptr->load(filepath.c_str());
		}

		void MaterialComponent::update_material()
		{
			if (!m_material_ptr)
			{
				auto num = m_material_ptr->get_param_map_count();
				for (unsigned int i = 0; i < num; ++i)
				{
					auto param_map = m_material_ptr->get_param_map(i);
					if (!param_map) continue;
					for (auto iter = param_map->m_semantic_map.begin(); iter != param_map->m_semantic_map.end(); ++i)
					{
						// update semantic
						update_semantic_param(param_map, iter->first, iter->second);
					}
				}
			}
		}

		void MaterialComponent::update_semantic_param(render::ParameterMapPtr param_map, std::string name, render::SemanticType semantic)
		{
			switch (semantic)
			{
			case water::render::SemanticNone:
				break;
			case water::render::SemanticWVP:
				auto trans_comp = GET_COMPONENT(m_game_object, TransformComponent);
				if (trans_comp == nullptr) break;
				auto world_trans = trans_comp->get_world_transformation();
				// todo
				break;
			default:
				break;
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

