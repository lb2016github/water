#include "mesh.h"

namespace water
{
	namespace render
	{
		void MeshDataManager::create_cube()
		{
			struct Vertex {
				Vertex(float p_x, float p_y, float p_z, float c_x, float c_y, float c_z) : position(p_x, p_y, p_z), color(c_x, c_y, c_z) {}
				math3d::Vector3 position;
				math3d::Vector3 color;
			};
			std::vector<math3d::Vector3> positions = {
				{-1, 0, 0},
				{1, 0, 0},
				{0, 0, 2},
				{0, 2, 1},
			};
			std::vector<math3d::Vector2> coords = {
				{0, 1},
				{1, 0},
				{0.5, 0.5},
				{0, 0.5},
			};
			std::shared_ptr<MeshData> mesh_data_ptr = std::make_shared<MeshData>();
			add_data_to_buffer(positions, mesh_data_ptr->base_pos);
			add_data_to_buffer(coords, mesh_data_ptr->base_coord);
			mesh_data_ptr->num_vertex = positions.size();
		}
		void MeshDataManager::add_data_to_buffer(std::vector<math3d::Vector3>& data, int & start_pos)
		{
			start_pos = m_vec3_buffer.size();
			for (auto iter = data.begin(); iter != data.end(); ++iter)
			{
				m_vec3_buffer.push_back(*iter);
			}
		}
		void MeshDataManager::add_data_to_buffer(std::vector<math3d::Vector2>& data, int & start_pos)
		{
			start_pos = m_vec2_buffer.size();
			for (auto iter = data.begin(); iter != data.end(); ++iter)
			{
				m_vec2_buffer.push_back(*iter);
			}
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

