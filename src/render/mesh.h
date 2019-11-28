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
			std::vector<math3d::Vector3> position;
			std::vector<math3d::Vector3> normal;
			std::vector<math3d::Vector4> color;
			std::vector<math3d::Vector2> coordinate;
			std::vector<math3d::Vector3> tangent;
			std::vector<math3d::Vector4> bone_id;
			std::vector<math3d::Vector4> bone_weight;
			std::vector<unsigned int> index_data;
			MeshMode mode;

			bool dirty = { true };
		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


	}
}

#endif // !WATER_MESH_H
