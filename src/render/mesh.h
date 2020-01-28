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
#include "world/animation/skeleton.h"


namespace water
{
	namespace render
	{
		class MeshData;
		typedef std::shared_ptr<MeshData> MeshDataPtr;

		/*
		@brief class of mesh data
		note: check whether mutex is needed for dynamic mesh
		*/
		class MeshData: std::enable_shared_from_this<MeshData>
		{
		public:
			static const unsigned char BIT_POSITION = 1;
			static const unsigned char BIT_NORMAL = 2;
			static const unsigned char BIT_COLOR = 3;
			static const unsigned char BIT_COORDINATE = 4;
			static const unsigned char BIT_TANGENT = 5;
			static const unsigned char BIT_SKIN = 6;
			static const unsigned char BIT_INDEX = 7;
			typedef unsigned long VertexFormat;

		public:
			MeshData(const std::string& filepath, int mesh_idx, MeshMode mesh_mode);
			MeshData(MeshMode mesh_mode);
			void updateFormat();
		public:
			static MeshDataPtr combineMeshes(const std::vector<MeshDataPtr>& meshList);

		public:
			WATER_ID mesh_id;
			VertexFormat format;
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
			/* usage */
			MeshUsage usage{ MeshUsage::STATIC_DRAW };
			/* skeleton id */
			world::SkeletonID skeID;

			bool dirty = { true };
		};
	}
}

#endif // !WATER_MESH_H
