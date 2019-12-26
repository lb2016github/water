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
			virtual std::vector<render::MeshDataPtr> load_all_mesh(const std::string& filename);
			virtual render::MeshDataPtr load_sub_mesh(const std::string& filename, int mesh_idx);
			virtual render::MeshDataPtr load_combined_mesh(const std::string& filename);
			virtual world::AnimationClipData load_animation(const std::string& filename);
		};
	}
}

#endif // !WATER_MESH_LOADER_H
