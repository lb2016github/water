#include "mesh_loader/MeshLoader.h"
#include <memory>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "scene.h"

namespace water
{
	render::MeshDataPtr water::MeshLoader::load_mesh(const std::string & filename)
	{
		render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>();
		return data_ptr;
	}
	render::MeshDataPtr MeshLoader::do_load_mesh(const std::string & filename)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);
		unsigned int num_meshes = scene->mNumMeshes;
		for (int i = 0; i < num_meshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[i];
			unsigned int num_vertices = mesh->mNumVertices;

		}
		// load from scene
		return render::MeshDataPtr();
	}
}

