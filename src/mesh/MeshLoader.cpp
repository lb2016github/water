#include "MeshLoader.h"
#include <memory>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "scene.h"
#include "filesystem/filesystem.h"
#include "common/log.h"
#include <string>
#include <queue>

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

		std::vector<render::MeshDataPtr> MeshLoader::load_all_mesh(const std::string & filename)
		{
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(filename);
			std::vector<render::MeshDataPtr> meshes;
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(abs_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);

			// load meshes and combine meshes directly
			unsigned int base_index = 0;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>(filename, i, render::TRIANGLES);
				aiMesh* mesh = scene->mMeshes[i];
				// load vertex data
				unsigned int num_vertices = mesh->mNumVertices;
				for (auto i = 0; i < num_vertices; ++i)
				{
					aiVector3D* tmp = &(mesh->mVertices[i]);
					data_ptr->position.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					if (mesh->mNormals != nullptr)
					{
						tmp = &(mesh->mNormals[i]);
						data_ptr->normal.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					if (mesh->mColors[0] != nullptr)
					{
						aiColor4D clr = mesh->mColors[0][i]; // todo currently assume only one color
						data_ptr->color.push_back(math3d::Vector4(clr.r, clr.g, clr.b, clr.a));
					}
					if (mesh->HasTextureCoords(0))
					{
						tmp = &(mesh->mTextureCoords[0][i]);	// todo currently assume only one texture coordinate is supporetd
						data_ptr->coordinate.push_back(math3d::Vector2(tmp->x, tmp->y));
					}
					if (mesh->mTangents != nullptr)
					{
						tmp = &(mesh->mTangents[i]);
						data_ptr->tangent.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
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

				meshes.push_back(data_ptr);
			}
			return meshes;
		}
		render::MeshDataPtr MeshLoader::load_sub_mesh(const std::string & filename, int mesh_idx)
		{
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(filename);
			render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>(filename, mesh_idx, render::TRIANGLES);
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(abs_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);

			// load meshes and combine meshes directly
			unsigned int base_index = 0;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				if (mesh_idx >= 0 && i != mesh_idx) continue;
				aiMesh* mesh = scene->mMeshes[i];
				// load vertex data
				unsigned int num_vertices = mesh->mNumVertices;
				for (auto i = 0; i < num_vertices; ++i)
				{
					aiVector3D* tmp = &(mesh->mVertices[i]);
					data_ptr->position.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					if (mesh->mNormals != nullptr)
					{
						tmp = &(mesh->mNormals[i]);
						data_ptr->normal.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					if (mesh->mColors[0] != nullptr)
					{
						aiColor4D clr = mesh->mColors[0][i]; // todo currently assume only one color
						data_ptr->color.push_back(math3d::Vector4(clr.r, clr.g, clr.b, clr.a));
					}
					if (mesh->mTextureCoords[0] != nullptr)
					{
						tmp = &(mesh->mTextureCoords[0][i]);	// todo currently assume only one texture coordinate is supporetd
						data_ptr->coordinate.push_back(math3d::Vector2(tmp->x, tmp->y));
					}
					if (mesh->mTangents != nullptr)
					{
						tmp = &(mesh->mTangents[i]);
						data_ptr->tangent.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
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
		render::MeshDataPtr MeshLoader::load_combined_mesh(const std::string & filename)
		{
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(filename);
			render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>(filename, -1, render::TRIANGLES);
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(abs_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);

			// TODO DELETE TEST CODE
			//load_animation(filename);

			// load meshes and combine meshes directly
			unsigned int base_index = 0;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				aiMesh* mesh = scene->mMeshes[i];
				// load vertex data
				unsigned int num_vertices = mesh->mNumVertices;
				for (unsigned int i = 0; i < num_vertices; ++i)
				{
					aiVector3D* tmp = &(mesh->mVertices[i]);
					data_ptr->position.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					if (mesh->mNormals != nullptr)
					{
						tmp = &(mesh->mNormals[i]);
						data_ptr->normal.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					if (mesh->mColors[0] != nullptr)
					{
						aiColor4D clr = mesh->mColors[0][i]; // todo currently assume only one color
						data_ptr->color.push_back(math3d::Vector4(clr.r, clr.g, clr.b, clr.a));
					}
					if (mesh->mTextureCoords[0] != nullptr)
					{
						tmp = &(mesh->mTextureCoords[0][i]);	// todo currently assume only one texture coordinate is supporetd
						data_ptr->coordinate.push_back(math3d::Vector2(tmp->x, tmp->y));
					}
					if (mesh->mTangents != nullptr)
					{
						tmp = &(mesh->mTangents[i]);
						data_ptr->tangent.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					// todo load bone info
				}

				unsigned int num_indices = mesh->mNumFaces * 3;
				for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
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
		aiNode* getNodeByName(aiNode* node, const char* name)
		{
			if (strcmp(node->mName.C_Str(), name) ==0) return node;
			for (int i = 0; i < node->mNumChildren; ++i)
			{
				auto tmp = getNodeByName(node->mChildren[i], name);
				if (tmp != nullptr) return tmp;
			}
			return nullptr;

		};

		void printNode(aiNode* node, int prefex)
		{
			std::string preStr = "";
			for (int i = 0; i < prefex; ++i)
			{
				preStr += "   |";
			}

			log_info("%s%s", preStr.c_str(), node->mName.C_Str());
			for (int i = 0; i < node->mNumChildren; ++i)
			{
				printNode(node->mChildren[i], prefex + 1);
			}
		}

		aiNode* getRootBone(aiNode* rootNode, const char* name)
		{
			aiNode* node = getNodeByName(rootNode, name);
			while (node)
			{
				aiNode* parent = node->mParent;
				if (!parent) return node;
				std::string pName = parent->mName.C_Str();
				if (pName.find(name) == 0 && pName.find("Assimp") != std::string::npos)
				{
					return node;
				}
				else
				{
					node = parent;
				}
			}
			return nullptr;
		}

		world::SkeletonPtr createSkeletonByRootBone(aiNode* rootNode)
		{
			// hierachy first traverse
			std::queue<aiNode*> nodes;
			nodes.push(rootNode);

			// save nodes
			std::vector<world::Joint> joints;
			while (nodes.size() > 0)
			{
				aiNode* node = nodes.front();
				nodes.pop();
				// create Joint with aiNode
				world::Joint joint;
				joint.m_name = node->mName.C_Str();
				auto& mtx = node->mTransformation;
				joint.m_invBindPose = math3d::Matrix(
					mtx.a1, mtx.a2, mtx.a3, mtx.a4,
					mtx.b1, mtx.b2, mtx.b3, mtx.b4,
					mtx.c1, mtx.c2, mtx.c3, mtx.c4,
					mtx.d1, mtx.d2, mtx.d3, mtx.d4
					);
				for (int i = 0; i < joints.size(); ++i)
				{
					if (strcmp(node->mName.C_Str(), joints[i].m_name.c_str()) == 0)
					{
						joint.m_parentIndex = i;
					}
				}
				joints.push_back(joint);
				// add children to nodes
				for (int i = 0; i < node->mNumChildren; ++i)
				{
					nodes.push(node->mChildren[i]);
				}
			}
			world::SkeletonPtr skPtr = std::make_shared<world::Skeleton>(joints.size());
			for (int i = 0; i < joints.size(); ++i)
			{
				skPtr->m_joints[i] = joints[i];
			}
			return skPtr;
		}

		world::AnimationClipData MeshLoader::load_animation(const std::string& filename)
		{
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(filename);
			render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>(filename, -1, render::TRIANGLES);
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(abs_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);
			if (!scene->HasAnimations()) return world::AnimationClipData();
			printNode(scene->mRootNode, 0);
			// 1. load skeletons
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				auto meshPtr = scene->mMeshes[i];
				std::vector<world::Joint*> joints;
				if (meshPtr->mNumBones <= 0) continue;
				world::SkeletonPtr skePtr = nullptr;
				for (int j = 0; j < meshPtr->mNumBones; ++j)
				{
					auto bone = meshPtr->mBones[j];
					// init skeleton
					if (!skePtr)
					{
						aiNode* rootBoneNode = getRootBone(scene->mRootNode, bone->mName.C_Str());
						skePtr = createSkeletonByRootBone(rootBoneNode);
					}
					world::Joint* joint = new world::Joint();
					joint->m_name = bone->mName.C_Str();
					auto& mtx = bone->mOffsetMatrix;
					joint->m_invBindPose = math3d::Matrix(
						mtx.a1, mtx.a2, mtx.a3, mtx.a4,
						mtx.b1, mtx.b2, mtx.b3, mtx.b4,
						mtx.c1, mtx.c2, mtx.c3, mtx.c4,
						mtx.d1, mtx.d2, mtx.d3, mtx.d4
						);
					joints.push_back(joint);
				}
			}


			// 2. load animation
			for (int i = 0; i < scene->mNumAnimations; ++i)
			{
				// todo
				auto anim = scene->mAnimations[i];
				// 1. load skeleton
				// todo check whether the skeleton has been created
				world::SkeletonPtr sk_ptr = std::make_shared<world::Skeleton>(anim->mNumChannels);
				world::AnimationClipPtr anim_clip_ptr = std::make_shared<world::AnimationClip>(sk_ptr, anim->mDuration);
				// for every bone
				for (int j = 0; j < anim->mNumChannels; ++i)
				{
					auto nodeAnim = anim->mChannels[j];
					auto boneName = nodeAnim->mNodeName;
					auto idx = sk_ptr->getJointIndexByName(boneName.C_Str());
					if (idx < 0) continue;
					// update skeleton info
					world::JointFrameData data(nodeAnim->mNumPositionKeys, nodeAnim->mNumRotationKeys, nodeAnim->mNumScalingKeys);
					for (int k = 0; k < nodeAnim->mNumPositionKeys; ++k)
					{
						auto trans = nodeAnim->mPositionKeys[k];
						// todo check whether need to multiply 1000
						data.m_trans[k].setData(trans.mTime * 1000, trans.mValue.x, trans.mValue.y, trans.mValue.z);
					}
					for (int k = 0; k < nodeAnim->mNumScalingKeys; ++k)
					{
						auto scale = nodeAnim->mScalingKeys[k];
						// todo check whether need to multiply 1000
						data.m_scale[k].setData(scale.mTime * 1000, scale.mValue.x, scale.mValue.y, scale.mValue.z);
					}
					for (int k = 0; k < nodeAnim->mNumRotationKeys; ++k)
					{
						auto rot = nodeAnim->mRotationKeys[k];
						// todo check whether need to multiply 1000
						data.m_rot[k].setData(rot.mTime * 1000, rot.mValue.w, rot.mValue.x, rot.mValue.y, rot.mValue.z);
					}
					anim_clip_ptr->setJointFrameData(idx, std::move(data));
				}
				// save animation
				world::AnimationClipManager::instance()->getAnimClipDataPtr(sk_ptr->m_id)->addAnimClip(anim->mName.C_Str(), anim_clip_ptr);
			}
			return world::AnimationClipData();
		}
	}
}

