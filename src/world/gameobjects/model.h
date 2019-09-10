#ifndef WATER_MODEL_H
#define WATER_MODEL_H

#include "render/render_object.h"
#include "space_object.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "world/components/render_component.h"

namespace water
{
	namespace world
	{
		class Model : public SpaceObjectTpl<MeshComponent, MaterialComponent, RenderComponent>
		{
		public:
			// init from file
			virtual void load_from_file(std::string& filepath);

		protected:
			virtual std::set<ComponentTag> get_comp_tags();
		};

		DECL_SHARED_PTR(Model);
		DECL_WEEK_PTR(Model);
	}
}

#endif // !WATER_MODEL_H
