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
			int base_pos;
			int base_normal;
			int base_coord;
			int base_tangent;
			unsigned int base_index;
			unsigned int num_vertex;
			unsigned int num_index;
			MeshData() : base_pos(-1), base_normal(-1), base_coord(-1), base_tangent(-1), base_index(-1), num_vertex(-1), num_index(-1) {}
		};

		struct MeshDataCreator
		{
			void create_box();
		};


		class MeshDataManager
		{
		private:
			std::map<std::string, MeshData> m_data;
			std::vector<math3d::Vector3> m_vec3_buffer;
			std::vector<math3d::Vector2> m_vec2_buffer;
			std::vector<math3d::Matrix> m_mtx_buffer;

			friend struct MeshDataCreator;
		};
	}
}

#endif // !WATER_MESH_H
