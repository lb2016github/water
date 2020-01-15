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
			static const unsigned char BIT_POSITION = 0;
			static const unsigned char BIT_NORMAL = 1;
			static const unsigned char BIT_COLOR = 2;
			static const unsigned char BIT_COORDINATE = 3;
			static const unsigned char BIT_TANGENT = 4;
			static const unsigned char BIT_SKIN = 5;
			static const unsigned char BIT_INDEX = 6;
			typedef unsigned long VertexFormat;

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
			void updateFormat()
			{
				if (position.size() > 0)
				{
					format |= 1 << BIT_POSITION;
				}
				if (normal.size() > 0)
				{
					format |= 1 << BIT_NORMAL;
				}
				if (color.size() > 0)
				{
					format |= 1 << BIT_COLOR;
				}
				if (coordinate.size() > 0)
				{
					format |= 1 << BIT_COORDINATE;
				}
				if (tangent.size() > 0)
				{
					format |= 1 << BIT_TANGENT;
				}
				if (joint_indices.size() > 0)
				{
					format |= 1 << BIT_SKIN;
				}
				if (index_data.size > 0)
				{
					format |= 1 << BIT_INDEX;
				}
			}


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
			/* skeleton id */
			world::SkeletonID skeID;

			bool dirty = { true };
		};
		typedef std::shared_ptr<MeshData> MeshDataPtr;


	}
}

#endif // !WATER_MESH_H
