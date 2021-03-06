#ifndef WATER_MODEL_H
#define WATER_MODEL_H

#include "render/render_object.h"
#include "space_object.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"
#include "world/components/render_component.h"
#include "space_object.h"

namespace water
{
	namespace world
	{
		class Model : public SpaceObject, public ComponentObject<MeshComponent, MaterialComponent, RenderComponent>
		{
		public:
			// init from file
			virtual void load_from_file(std::string& filepath);
		};

		DECL_SHARED_PTR(Model);
		DECL_WEEK_PTR(Model);
	}
}

#endif // !WATER_MODEL_H
