#ifndef WATER_MATERIAL_COMPONENT_H
#define WATER_MATERIAL_COMPONENT_H

#include "component.h"
#include "world/gameobjects/game_object.h"
#include "render/material.h"

namespace water
{
	namespace world
	{
		class MaterialComponent : public Component
		{
		public:
			MaterialComponent() : MaterialComponent(nullptr) {};
			MaterialComponent(GameObject* game_object);
			MaterialComponent(const MaterialComponent& comp) : MaterialComponent(comp, nullptr) {};
			MaterialComponent(const MaterialComponent& comp, GameObject* game_object);
			MaterialComponent& operator = (const MaterialComponent& comp);
			virtual ~MaterialComponent() override;

			// component info
			static ComponentTag tag;
			static Component* create_component(GameObject*);

		public:
			/*
			* @brief: set parameter to material
			*
			* @param name: name of parameter
			* @param pvalue: value of parameter
			* @param index: index of render pass, the default value is 0
			* 
			* @return void
			*/
			template<class T>
			void set_param(std::string name, T& value, unsigned int index = 0);

			// check has certern param
			bool has_param(std::string name, unsigned int index = 0);

			// get material
			render::MaterialPtr get_material();
			void load_from_file(const std::string& filepath);

		private:
			render::MaterialPtr m_material_ptr;
		};

		template<class T>
		inline void MaterialComponent::set_param(std::string name, T& value, unsigned int index)
		{
			auto ptr = m_material_ptr->get_param_map(index);
			if (!ptr) return;
			ptr->set_param(name, value);
		}

	}
}

#endif // !WATER_MATERIAL_COMPONENT_H
