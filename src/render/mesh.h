#ifndef WATER_MESH_H
#define WATER_MESH_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "math3d\math3d.hpp"
#include "common/common.h"

#define MESH_ID_TYPE unsigned int

namespace water
{
	namespace render
	{
		struct MeshData
		{
			MESH_ID_TYPE mesh_id;
			std::vector<math3d::Vector3> position;
			std::vector<math3d::Vector3> normal;
			std::vector<math3d::Vector4> color;
			std::vector<math3d::Vector2> coordinate;
			std::vector<math3d::Vector3> tangent;
			std::vector<unsigned int> index_data;
		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


	}
}

#endif // !WATER_MESH_H
