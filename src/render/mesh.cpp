#include "mesh.h"


namespace water
{
	namespace render
	{
		MeshData::MeshData(const std::string& filepath, int mesh_idx, MeshMode mesh_mode) : mode(mesh_mode)
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
		MeshData::MeshData(MeshMode mesh_mode) : mode(mesh_mode)
		{ 
			mesh_id = create_id(); 
		}
		void MeshData::updateFormat()
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
			if (index_data.size() > 0)
			{
				format |= 1 << BIT_INDEX;
			}
		}
		MeshDataPtr MeshData::combineMeshes(const std::vector<MeshDataPtr>& meshList)
		{
			if (meshList.size() == 0) return nullptr;
			if (meshList.size() == 1)
			{
				return meshList[0];
			}
			// check skeleton, vertex format and mode
			world::SkeletonID skId = meshList[0]->skeID;
			render::MeshData::VertexFormat format = meshList[0]->format;
			MeshMode meshMode = meshList[0]->mode;
			for each (auto ptr in meshList)
			{
				if (ptr->skeID != skId) return nullptr;
				if (ptr->format != format) return nullptr;
				if (ptr->mode != meshMode) return nullptr;
			}
			// do combine mesh
			unsigned int baseIndex = 0;
			render::MeshDataPtr dataPtr = std::make_shared<render::MeshData>(meshMode);
			for each (auto meshPtr in meshList)
			{
				if ((format & render::MeshData::BIT_POSITION) > 0)
				{
					dataPtr->position.insert(dataPtr->position.end(), meshPtr->position.begin(), meshPtr->position.end());
				}
				if ((format & render::MeshData::BIT_NORMAL) > 0)
				{
					dataPtr->normal.insert(dataPtr->normal.end(), meshPtr->normal.begin(), meshPtr->normal.end());
				}
				if ((format & render::MeshData::BIT_COLOR) > 0)
				{
					dataPtr->color.insert(dataPtr->color.end(), meshPtr->color.begin(), meshPtr->color.end());
				}
				if ((format & render::MeshData::BIT_COORDINATE) > 0)
				{
					dataPtr->coordinate.insert(dataPtr->coordinate.end(), meshPtr->coordinate.begin(), meshPtr->coordinate.end());
				}
				if ((format & render::MeshData::BIT_TANGENT) > 0)
				{
					dataPtr->tangent.insert(dataPtr->tangent.end(), meshPtr->tangent.begin(), meshPtr->tangent.end());
				}
				if ((format & render::MeshData::BIT_SKIN) > 0)
				{
					dataPtr->joint_indices.insert(dataPtr->joint_indices.end(), meshPtr->joint_indices.begin(), meshPtr->joint_indices.end());
					dataPtr->joint_weights.insert(dataPtr->joint_weights.end(), meshPtr->joint_weights.begin(), meshPtr->joint_weights.end());
				}
				if ((format & render::MeshData::BIT_INDEX) > 0)
				{
					for (auto iter = meshPtr->index_data.begin(); iter != meshPtr->index_data.end(); ++iter)
					{
						dataPtr->index_data.emplace_back(*iter + baseIndex);
					}
				}
				baseIndex = dataPtr->index_data.size();
			}
			dataPtr->updateFormat();
			return dataPtr;

		}
	}
}
