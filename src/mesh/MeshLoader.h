#ifndef WATER_MESH_LOADER_H
#define WATER_MESH_LOADER_H
#include "IMeshLoader.h"

namespace water
{
	namespace mesh
	{
		class MeshLoader : public IMeshLoader
		{
		public:
			virtual render::MeshDataPtr load_mesh(const std::string& filename);
		};
	}
}

#endif // !WATER_MESH_LOADER_H
