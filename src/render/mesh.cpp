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
			std::vector<Vertex> vertexs = {
				{-1, 0, 0, 255, 0, 0},
				{1, 0, 0, 255, 255, 0},
				{0, 0, 2, 255, 0, 255},
				{0, 2, 1, 0, 255, 0},
			};


		}
		void MeshDataManager::add_data_to_buffer(std::vector<math3d::Vector3>& data, int & start_pos)
		{
		}
	}
}

