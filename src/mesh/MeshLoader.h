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
			virtual void load_animation(const std::string& filename);
		};

		class ModelData
		{
		public:
			/*
			init ModelData with filename and meshIdx
			@param filepath: filepath of assert
			@param meshIdx: mesh idx of 
			*/
			ModelData(const std::string& filepath);
		public:
			/* filename of model */
			std::string m_filepath{ "" };
			/* mesh of model */
			render::MeshDataPtr m_meshPtr{ nullptr };
			/* skeleton pointer */
			world::SkeletonPtr m_skPtr{ nullptr };
			/* animation list */
			world::AnimationClipData m_animClipData;
		};
	}
}

#endif // !WATER_MESH_LOADER_H
