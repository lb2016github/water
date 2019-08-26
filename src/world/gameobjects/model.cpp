#include "model.h"
#include "world/components/component_const.h"
#include "world/components/mesh_component.h"

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
		}
		Model::Model(const Model& model)
		{
		}
		Model& Model::operator=(const Model& model)
		{
			// TODO: 在此处插入 return 语句
		}
		Model::~Model()
		{
		}
		render::MeshDataPtr Model::get_mesh()
		{
			MeshComponent* mesh_comp = (MeshComponent*)get_component(COMP_MESH);
			return mesh_comp->get_mesh_ptr();
		}
	}
}