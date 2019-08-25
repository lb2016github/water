#include "model.h"
#include "world/components/mesh_component.h"
#include "world/components/transform_component.h"

namespace water
{
	namespace world
	{
		Model::Model()
		{
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
		render::MaterialPtr Model::get_material()
		{
			return render::MaterialPtr();
		}
		render::MeshPtr Model::get_mesh()
		{
			return render::MeshPtr();
		}
	}
}