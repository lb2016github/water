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
			// set parameter
			void set_param(std::string name, render::ParamValue& pvalue);

			// get material
			render::MaterialPtr get_material();
			void load_from_file(const std::string& filepath);

		private:
			render::MaterialPtr m_material_ptr;
		};

	}
}

#endif // !WATER_MATERIAL_COMPONENT_H
