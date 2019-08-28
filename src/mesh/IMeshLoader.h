#ifndef WATER_I_MESH_LOADER_H
#define WATER_I_MESH_LOADER_H

#include "common/common.h"
#include "render/mesh.h"
#include <string>

namespace water
{
	namespace mesh
	{
		WaterInterface IMeshLoader
		{
			virtual render::MeshDataPtr load_mesh(const std::string& filename) = 0;
		};

		IMeshLoader* get_mesh_loader();
	}
}


#endif // !WATER_I_MESH_LOADER_H
