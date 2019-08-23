#ifndef WATER_MESH_H
#define WATER_MESH_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "math3d\math3d.hpp"

namespace water
{
	namespace render
	{

		struct MeshData
		{
			unsigned int mesh_id;
			math3d::Vector3* pos_data;
			math3d::Vector3* normal_data;
			math3d::Vector4* color_data;
			math3d::Vector2* coord_data;
			math3d::Vector3* tangent_data;
			unsigned int* index_data;
			unsigned int num_vertex;
			unsigned int num_index;
			MeshData();
			~MeshData();

		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


		class MeshDataManager
		{
		public:
			void create_cube();
			void add_mesh(MeshDataPtr mesh_data_ptr);

			static unsigned int new_mesh_id();
			static unsigned int cur_index;

		private:
			std::map<unsigned int, MeshDataPtr> m_data;

			friend struct MeshDataCreator;
		};
	}
}

#endif // !WATER_MESH_H
