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
			void* pos_data;
			void* normal_data;
			void* coord_data;
			void* tangent_data;
			void* index_data;
			unsigned int num_vertex;
			unsigned int num_index;
			MeshData() : pos_data(nullptr), normal_data(nullptr), coord_data(nullptr), tangent_data(nullptr), index_data(nullptr)
			{
				mesh_id = MeshDataManager::new_mesh_id();
			}
		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


		class MeshDataManager
		{
		public:
			void create_cube();
			void add_data_to_buffer(std::vector<math3d::Vector3>& data, void** data_ptr);
			void add_data_to_buffer(std::vector<math3d::Vector2>& data, void** data_ptr);
			void add_mesh(MeshDataPtr mesh_data_ptr);

			static unsigned int new_mesh_id();
			static unsigned int cur_index;

		private:
			std::map<unsigned int, MeshDataPtr> m_data;
			std::vector<math3d::Vector3> m_vec3_buffer;
			std::vector<math3d::Vector2> m_vec2_buffer;
			std::vector<math3d::Matrix> m_mtx_buffer;

			friend struct MeshDataCreator;
		};
	}
}

#endif // !WATER_MESH_H
