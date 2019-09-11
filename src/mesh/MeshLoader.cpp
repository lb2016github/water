#include "MeshLoader.h"
#include <memory>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "scene.h"

namespace water
{
	namespace mesh
	{

		static IMeshLoader* loader_ptr = nullptr;

		IMeshLoader* get_mesh_loader()
		{
			if (loader_ptr == nullptr)
			{
				loader_ptr = new MeshLoader();
			}
			return loader_ptr;
		}

		render::MeshDataPtr MeshLoader::load_mesh(const std::string & filename)
		{
			render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>();
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);

			// load meshes and combine meshes directly
			unsigned int base_index = 0;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				aiMesh* mesh = scene->mMeshes[i];
				// load vertex data
				unsigned int num_vertices = mesh->mNumVertices;
				for (auto i = 0; i < num_vertices; ++i)
				{
					aiVector3D tmp = mesh->mVertices[i];
					data_ptr->position.push_back(math3d::Vector3(tmp.x, tmp.y, tmp.z));
					if (mesh->mNormals != nullptr)
					{
						tmp = mesh->mNormals[i];
						data_ptr->normal.push_back(math3d::Vector3(tmp.x, tmp.y, tmp.z));
					}
					if (mesh->mColors[0] != nullptr)
					{
						aiColor4D clr = mesh->mColors[0][i]; // todo currently assume only one color
						data_ptr->color.push_back(math3d::Vector4(clr.r, clr.g, clr.b, clr.a));
					}
					if (mesh->mTextureCoords[0] != nullptr)
					{
						tmp = mesh->mTextureCoords[0][i];	// todo currently assume only one texture coordinate is supporetd
						data_ptr->coordinate.push_back(math3d::Vector2(tmp.x, tmp.y));
					}
					if (mesh->mTangents != nullptr)
					{
						tmp = mesh->mTangents[i];
						data_ptr->tangent.push_back(math3d::Vector3(tmp.x, tmp.y, tmp.z));
					}
					// todo load bone info
				}

				unsigned int num_indices = mesh->mNumFaces * 3;
				for (auto j = 0; j < mesh->mNumFaces; ++j)
				{
					auto face = mesh->mFaces[j];
					assert(face.mNumIndices == 3);
					data_ptr->index_data.push_back(base_index + face.mIndices[0]);
					data_ptr->index_data.push_back(base_index + face.mIndices[1]);
					data_ptr->index_data.push_back(base_index + face.mIndices[2]);
				}
				base_index += num_vertices;
			}
			return data_ptr;
		}
	}
}

