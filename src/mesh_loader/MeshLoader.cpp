#include "mesh_loader/MeshLoader.h"
#include <memory>

namespace water
{
	render::MeshDataPtr water::MeshLoader::load_mesh(const std::string & filename)
	{
		render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>();
		// todo
		return data_ptr;
	}
}

