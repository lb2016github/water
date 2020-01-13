#ifndef WATER_I_MESH_LOADER_H
#define WATER_I_MESH_LOADER_H

#include "common/common.h"
#include "render/mesh.h"
#include <string>
#include "world/animation/animation.h"

namespace water
{
	namespace mesh
	{
		WaterInterface IMeshLoader
		{
			virtual std::vector<render::MeshDataPtr> load_all_mesh(const std::string& filename) = 0;
			virtual render::MeshDataPtr load_sub_mesh(const std::string& filename, int mesh_idx) = 0;
			virtual render::MeshDataPtr load_combined_mesh(const std::string& filename) = 0;
			virtual void load_animation(const std::string& filename) = 0;
		};

		IMeshLoader* get_mesh_loader();
	}
}


#endif // !WATER_I_MESH_LOADER_H
