#ifndef WATER_MESH_H
#define WATER_MESH_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "math3d\math3d.hpp"
#include "common/common.h"
#include <string>
#include "render_const.h"
#include "common/util.h"


namespace water
{
	namespace render
	{
		struct MeshData
		{
			MeshData(const std::string& filepath, int mesh_idx, MeshMode mesh_mode): mode(mesh_mode)
			{
				WATER_ID hash = 5333 + mesh_idx;
				auto char_str = filepath.c_str();
				int c;
				while (c = *char_str++)
				{
					hash = ((hash << 5) + hash) + c;
				}
				mesh_id = hash;
			}
			MeshData(MeshMode mesh_mode) : mode(mesh_mode) { mesh_id = create_id(); }
			WATER_ID mesh_id;
			/* position of vertex */
			std::vector<math3d::Vector3> position;
			/* normal of vertex */
			std::vector<math3d::Vector3> normal;
			/* color of vertex */
			std::vector<math3d::Vector4> color;
			/* texture coordinate of vertex */
			std::vector<math3d::Vector2> coordinate;
			/* tangent of vertex */
			std::vector<math3d::Vector3> tangent;
			/* idx of joints */
			std::vector<math3d::Vector4I> joint_indices;
			/* weights of joints */
			std::vector<math3d::Vector4> joint_weights;
			/* element data of vertices */
			std::vector<unsigned int> index_data;
			/* mode of primitive */
			MeshMode mode;

			bool dirty = { true };
		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


	}
}

#endif // !WATER_MESH_H
