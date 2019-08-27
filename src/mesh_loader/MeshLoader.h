#ifndef WATER_MESH_LOADER_H
#define WATER_MESH_LOADER_H
#include "mesh_loader/IMeshLoader.h"

namespace water
{
	class MeshLoader : public IMeshLoader
	{
	public:
		virtual render::MeshDataPtr load_mesh(const std::string& filename);

	protected:
		render::MeshDataPtr do_load_mesh(const std::string& filename);

	};
}

#endif // !WATER_MESH_LOADER_H
