#ifndef WATER_ASSIMP_LOADER_H
#define WATER_ASSIMP_LOADER_H
#include "MeshLoader.h"
#include <vector>
#include <map>
#include "render/mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"


namespace water
{
	namespace loader
	{
		class AssimpLoader
		{
			struct VertexSkinData
			{
				unsigned int jointIdx;
				float weight;
			};
		public:
			AssimpLoader(const std::string& filepath);
			/*
			do load job, include loading skeleton, animation, mesh and skin
			*/
			void doLoad();
			/*
			combine meshes to one
			*/
			render::MeshDataPtr combine();
		protected:
			void loadSkeleton();
			void loadAnimation();
			void loadSkinData();
			void loadMesh();
			aiNode* getRootBone(const aiString& boneName);
		protected:
			/*
			create skeleton with root bone
			*/
			static world::SkeletonPtr createSkeletonByRootBone(aiNode* rootNode);
			/*
			print sturct node
			*/
			static void printNode(aiNode* node, int prefex = 2);
			/*
			get node by name
			*/
			static aiNode* getNodeByName(aiNode* rootNode, const aiString& name);
		private:
			std::string m_filepath{ "" };
			/* map of referenced skeletons, key is root bone name */
			std::map<aiString, world::SkeletonPtr> m_skMap;
			/* list of loaded meshes */
			std::vector<render::MeshDataPtr> m_meshList;
		private:
			/* define skin data for submesh */
			typedef std::map<unsigned int, std::vector<VertexSkinData>> MeshVertexSkinData;
			/* pointer to scene */
			const aiScene* m_scene{ nullptr };
			/* 
			saved skin data, to improve loading mesh data
			the data struct is {meshIdx: {vertexIdx: VertexSkinData}}
			*/
			std::map<unsigned int, MeshVertexSkinData> m_skinData;
		};

	}
}

#endif // !WATER_ASSIMP_LOADER_H
