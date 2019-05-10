#ifndef WATER_MESH_H
#define WATER_MESH_H
#include "math3d/math3d.hpp"
#include <vector>
#include <memory>
#include "common/common.h"
#include "glad/glad.h"

namespace water {
	namespace render {
		// 顶点数据
		struct Vertex {
			math3d::Vector3 position;
			math3d::Vector3 coordinate;
			math3d::Vector3 normal;
			math3d::Vector3 tangent;
		};
		// 顶点缓存，存放
		typedef std::vector<Vertex> VertexBuffer;
		typedef std::vector<int> ElementBuffer;

		struct MeshEntity {
			unsigned int base_index;
			unsigned int num_indices;
			unsigned int base_vertices;
		};

	}
}

#endif
