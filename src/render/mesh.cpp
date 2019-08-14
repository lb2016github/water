#include "mesh.h"
#include "common/common.h"

namespace water
{
	namespace render
	{
		MeshData::MeshData() : pos_data(nullptr), normal_data(nullptr), coord_data(nullptr), tangent_data(nullptr), index_data(nullptr)
		{
			mesh_id = MeshDataManager::new_mesh_id();
		}
		void MeshDataManager::create_cube()
		{
			std::shared_ptr<MeshData> mesh_data_ptr = std::make_shared<MeshData>();
			int vertex_num = 4;
			mesh_data_ptr->pos_data = new math3d::Vector3[vertex_num]{
				{-1, 0, 0},
				{1, 0, 0},
				{0, 0, 2},
				{0, 2, 1},
			};
			mesh_data_ptr->color_data = new math3d::Vector4[vertex_num]
			{
				{1, 0, 0, 1},
				{1, 0, 0, 1},
				{0.5, 0.5, 0, 1},
				{0, 0.5, 0.5, 1},
			};
			mesh_data_ptr->num_vertex = vertex_num;
		}
		MeshData::~MeshData()
		{
			SAFE_DELETE_ARRAY(pos_data);
			SAFE_DELETE_ARRAY(color_data);
			SAFE_DELETE_ARRAY(normal_data);
			SAFE_DELETE_ARRAY(coord_data);
			SAFE_DELETE_ARRAY(tangent_data);
			SAFE_DELETE_ARRAY(index_data);
		}

		void MeshDataManager::add_mesh(MeshDataPtr mesh_data_ptr)
		{
			m_data[mesh_data_ptr->mesh_id] = mesh_data_ptr;
		}

		unsigned int MeshDataManager::cur_index = 0;
		unsigned int MeshDataManager::new_mesh_id()
		{
			return ++cur_index;
		}
	}
}

