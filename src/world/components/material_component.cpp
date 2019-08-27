#include "material_component.h"
#include "render/material.h"

namespace water
{
	namespace world
	{

		Component* MaterialComponent::create_component(GameObject* gameobject)
		{
			return new MaterialComponent(gameobject);
		}

		render::MaterialPtr MaterialComponent::get_material()
		{
			return m_material_ptr;
		}

		void MaterialComponent::load_from_file(const std::string& filepath)
		{
			m_material_ptr->load(filepath.c_str());
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

