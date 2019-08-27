#include "model.h"
#include "world/components/component_const.h"
#include "world/components/mesh_component.h"
#include "world/components/material_component.h"

namespace water
{
	namespace world
	{
		Model::Model()
		{
			// add components
			add_component(COMP_MESH);
			add_component(COMP_RENDER);
			add_component(COMP_TRANSFORMATION);
			add_component(COMP_MATERIAL);
		}
		Model::Model(const Model& model): GameObject(model)
		{
		}
		Model& Model::operator=(const Model& model)
		{
			if (&model == this) return *this;

			GameObject::operator=(model);
			return *this;
		}
		Model::~Model()
		{
		}
		render::MaterialPtr Model::get_material()
		{
			MaterialComponent* comp = (MaterialComponent*)get_component(COMP_MATERIAL);
			return comp->get_material();
		}
		render::MeshDataPtr Model::get_mesh()
		{
			MeshComponent* mesh_comp = (MeshComponent*)get_component(COMP_MESH);
			return mesh_comp->get_mesh_ptr();
		}
		render::DrawCommand Model::get_draw_command()
		{
			render::DrawCommand dc;
			dc.draw_mode = render::TRIANGLE_TRIP;
			return dc;
		}
	}
}