#ifndef WATER_ASSIMP_LOADER_H
#define WATER_ASSIMP_LOADER_H
#include <vector>
#include <map>
#include "render/mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "world/animation/skeleton.h"
#include <function>


namespace water
{
	namespace world
	{
		class AssimpLoader
		{
			struct VertexSkinData
			{
				VertexSkinData() {}
				VertexSkinData(unsigned int jointIdx, float weight);
				unsigned int jointIdx{ 0 };
				float weight{ 0 };
			};
		public:
			AssimpLoader(const std::string& filepath);
			/*
			do load job, include loading skeleton, animation, mesh and skin
			*/
			void doLoad();
			/*
			combine meshes to one
			@return: if return ptr is not null, than combine meshes succeed, else failed.
				Many things may result in combining meshes fail, such as different skeleton, different vertex format.
			*/
			render::MeshDataPtr getCombinedMesh();
			std::vector<render::MeshDataPtr> getAllMesh();
		protected:
			void loadSkeleton();
			void loadAnimation();
			void loadSkinData();
			void loadMesh();
			aiNode* getRootBone(const aiString& boneName);
		protected:
			/*
			create skeleton with root bone
			@param subRootNdoes: list of affected nodes in animation
			*/
			static world::SkeletonPtr createSkeletonByRootBone(aiNode* rootNode, std::function<bool(aiNode*)> filter);
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
			/* ptr to created skeleton */
			world::SkeletonPtr m_skPtr;
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
			render::MeshDataPtr m_combinedMeshPtr{ nullptr };
		};

	}
}

#endif // !WATER_ASSIMP_LOADER_H
