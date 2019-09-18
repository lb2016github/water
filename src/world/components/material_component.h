#ifndef WATER_MATERIAL_COMPONENT_H
#define WATER_MATERIAL_COMPONENT_H

#include "base_component.h"
#include "world/gameobjects/game_object.h"
#include "render/material.h"
#include "render/draw_command.h"

namespace water
{
	namespace world
	{
		class MaterialComponent : public BaseComponent
		{
		public:
			MaterialComponent(GameObject* game_object);
			virtual MaterialComponent& operator = (const MaterialComponent& comp);
			virtual ~MaterialComponent() override;
			
			static const ComponentTag tag = COMP_MATERIAL;

		public:
			void set_material(render::MaterialPtr material);
			render::MaterialPtr get_material();
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

			// update material
			void update_material();


		protected:
			// update value of semantic param
			void update_semantic_param(render::ParameterMapPtr param_map, std::string name, render::SemanticType semantic);

		private:
			render::MaterialPtr m_material_ptr = { nullptr };
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
