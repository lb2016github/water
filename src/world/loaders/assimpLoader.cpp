#include "assimpLoader.h"
#include "filesystem/filesystem.h"
#include "assimp/postprocess.h"
#include "common/log.h"
#include <set>
#include <queue>
#include "world/animation/animation.h"

namespace water
{
	namespace world
	{
		AssimpLoader::AssimpLoader(const std::string& filepath):
			m_filepath(filepath)
		{
		}

		void AssimpLoader::doLoad()
		{
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(m_filepath);
			Assimp::Importer importer;
			m_scene = importer.ReadFile(abs_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_CalcTangentSpace);
			// load skeleton and animation
			loadSkeleton();
			loadAnimation();
			loadSkinData();
			loadMesh();
		}

		render::MeshDataPtr AssimpLoader::getCombinedMesh()
		{
			if (m_combinedMeshPtr) return m_combinedMeshPtr;
			if (m_meshList.size() < 0) return nullptr;
			if (m_meshList.size() == 1) return m_meshList[0];
			// check skeleton and vertex format
			world::SkeletonID skId = m_meshList[0]->skeID;
			render::MeshData::VertexFormat format = m_meshList[0]->format;
			for each (auto ptr in m_meshList)
			{
				if (ptr->skeID != skId) return nullptr;
				if (ptr->format != format) return nullptr;
			}
			// do combine mesh
			unsigned int baseIndex = 0;
			render::MeshDataPtr dataPtr = std::make_shared<render::MeshData>(m_filepath, -1, render::TRIANGLES);
			for each (auto meshPtr in m_meshList)
			{
				if (format & render::MeshData::BIT_POSITION > 0)
				{
					dataPtr->position.insert(dataPtr->position.end(), meshPtr->position.begin(), meshPtr->position.end());
				}
				if (format & render::MeshData::BIT_NORMAL > 0)
				{
					dataPtr->normal.insert(dataPtr->normal.end(), meshPtr->normal.begin(), meshPtr->normal.end());
				}
				if (format & render::MeshData::BIT_COLOR > 0)
				{
					dataPtr->color.insert(dataPtr->color.end(), meshPtr->color.begin(), meshPtr->color.end());
				}
				if (format & render::MeshData::BIT_COORDINATE > 0)
				{
					dataPtr->coordinate.insert(dataPtr->coordinate.end(), meshPtr->coordinate.begin(), meshPtr->coordinate.end());
				}
				if (format & render::MeshData::BIT_TANGENT > 0)
				{
					dataPtr->tangent.insert(dataPtr->tangent.end(), meshPtr->tangent.begin(), meshPtr->tangent.end());
				}
				if (format & render::MeshData::BIT_SKIN > 0)
				{
					dataPtr->joint_indices.insert(dataPtr->joint_indices.end(), meshPtr->joint_indices.begin(), meshPtr->joint_indices.end());
					dataPtr->joint_weights.insert(dataPtr->joint_weights.end(), meshPtr->joint_weights.begin(), meshPtr->joint_weights.end());
				}
				if (format & render::MeshData::BIT_INDEX > 0)
				{
					for (auto iter = meshPtr->index_data.begin(); iter != meshPtr->index_data.end(); ++iter)
					{
						dataPtr->index_data.emplace_back(*iter + baseIndex);
					}
				}
				baseIndex = dataPtr->index_data.size();
			}
			return dataPtr;
		}

		std::vector<render::MeshDataPtr> AssimpLoader::getAllMesh()
		{
			return m_meshList;
		}

		void AssimpLoader::loadSkeleton()
		{
			if (!m_scene->HasAnimations()) return;
			// 1. load skeletons
			for (int i = 0; i < m_scene->mNumMeshes; ++i)
			{
				auto meshPtr = m_scene->mMeshes[i];
				if (meshPtr->mNumBones <= 0) continue;
				auto bone = meshPtr->mBones[0];
				aiNode* rootBoneNode = getRootBone(bone->mName);
				if (!rootBoneNode) continue;
				// check whether has been loaded
				if (m_skMap.find(rootBoneNode->mName.C_Str()) != m_skMap.end()) continue;
				world::SkeletonPtr skePtr = createSkeletonByRootBone(rootBoneNode);
				
				// add to SkeletonManager
				world::SkeletonID skId = world::SkeletonManager::instance()->addSkeleton(skePtr);
				m_skMap[rootBoneNode->mName.C_Str()] = world::SkeletonManager::instance()->getSkeleton(skId);
			}
		}

		void AssimpLoader::loadAnimation()
		{
			for (int i = 0; i < m_scene->mNumAnimations; ++i)
			{
				auto anim = m_scene->mAnimations[i];
				assert(anim->mNumChannels > 0);

				// find the skeleton
				aiNode* rootBoneNode = getRootBone(anim->mChannels[0]->mNodeName);
				auto rst = m_skMap.find(rootBoneNode->mName.C_Str());
				assert(rst != m_skMap.end());
				auto skPtr = rst->second;

				world::AnimationClipPtr anim_clip_ptr = std::make_shared<world::AnimationClip>(skPtr, anim->mDuration);
				// for every bone
				for (int j = 0; j < anim->mNumChannels; ++i)
				{
					auto nodeAnim = anim->mChannels[j];
					auto boneName = nodeAnim->mNodeName;
					auto idx = skPtr->getJointIndexByName(boneName.C_Str());
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
				world::AnimationClipManager::instance()->getAnimClipDataPtr(skPtr->m_id)->addAnimClip(anim->mName.C_Str(), anim_clip_ptr);
			}
		}

		void AssimpLoader::loadMesh()
		{
			// load meshes and combine meshes directly
			unsigned int base_index = 0;
			for (int i = 0; i < m_scene->mNumMeshes; ++i)
			{
				render::MeshDataPtr data_ptr = std::make_shared<render::MeshData>(m_filepath, -1, render::TRIANGLES);
				aiMesh* mesh = m_scene->mMeshes[i];
				// get skin data
				auto rst = m_skinData.find(i);
				MeshVertexSkinData* skinDataPtr = nullptr;
				if (rst != m_skinData.end())
				{
					skinDataPtr = &(rst->second);
				}
				// load vertex data
				unsigned int num_vertices = mesh->mNumVertices;
				for (auto j = 0; j < num_vertices; ++j)
				{
					aiVector3D* tmp = &(mesh->mVertices[j]);
					data_ptr->position.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					if (mesh->mNormals != nullptr)
					{
						tmp = &(mesh->mNormals[j]);
						data_ptr->normal.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					if (mesh->mColors[0] != nullptr)
					{
						aiColor4D clr = mesh->mColors[0][j]; // todo currently assume only one color
						data_ptr->color.push_back(math3d::Vector4(clr.r, clr.g, clr.b, clr.a));
					}
					if (mesh->HasTextureCoords(0))
					{
						tmp = &(mesh->mTextureCoords[0][j]);	// todo currently assume only one texture coordinate is supporetd
						data_ptr->coordinate.push_back(math3d::Vector2(tmp->x, tmp->y));
					}
					if (mesh->mTangents != nullptr)
					{
						tmp = &(mesh->mTangents[j]);
						data_ptr->tangent.push_back(math3d::Vector3(tmp->x, tmp->y, tmp->z));
					}
					// load bone info
					if(mesh->mNumBones > 0)
					{
						auto tmp = skinDataPtr->find(j);
						assert(tmp != skinDataPtr->end());
						math3d::Vector4I jointIndex(0, 0, 0, 0);
						math3d::Vector4 jointWeight(0, 0, 0, 0);
						for (int n = 0; n < tmp->second.size(); ++n)
						{
							auto data = tmp->second[n];
							jointIndex[n] = data.jointIdx;
							jointWeight[n] = data.weight;
						}
						data_ptr->joint_indices.emplace_back(jointIndex);
						data_ptr->joint_weights.emplace_back(jointWeight);
					}
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
				data_ptr->updateFormat();
				m_meshList.push_back(data_ptr);
			}
		}

		void AssimpLoader::loadSkinData()
		{
			for (int i = 0; i < m_scene->mNumMeshes; ++i)
			{
				aiMesh* mesh = m_scene->mMeshes[i];
				if (mesh->mNumBones <= 0) continue;
				MeshVertexSkinData mvkd;
				// load from skin data from bone
				aiNode* rootBone = getRootBone(mesh->mBones[0]->mName);
				auto tmpRst = m_skMap.find(rootBone->mName.C_Str());
				assert(tmpRst != m_skMap.end());
				world::SkeletonPtr skPtr = tmpRst->second;
				// save skin data
				for (int j = 0; j < mesh->mNumBones; ++j)
				{
					aiBone* bone = mesh->mBones[j];
					unsigned int jointIdx = skPtr->getJointIndexByName(bone->mName.C_Str());
					for (int k = 0; k < bone->mNumWeights; ++k)
					{
						auto weight = bone->mWeights[k];
						auto tmp = mvkd.find(weight.mVertexId);
						if (tmp == mvkd.end())
						{
							mvkd[weight.mVertexId] = std::vector<VertexSkinData>();
						}
						// save VertexSkinData
						mvkd[weight.mVertexId].emplace_back(jointIdx, weight.mWeight);
					}
				}
				m_skinData[i] = mvkd;
			}
		}

		aiNode* AssimpLoader::getRootBone(const aiString& boneName)
		{
			aiNode* node = getNodeByName(m_scene->mRootNode, boneName);
			while (node)
			{
				aiNode* parent = node->mParent;
				if (!parent) return node;
				std::string pName = parent->mName.C_Str();
				// parent name starts with child name and contains Assimp
				if (pName.find(node->mName.C_Str()) == 0 && pName.find("Assimp") != std::string::npos)
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

		void AssimpLoader::printNode(aiNode* node, int prefex)
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

		aiNode* AssimpLoader::getNodeByName(aiNode* rootNode, const aiString& name)
		{
			// to speed up searching, use hierachy first search
			std::queue<aiNode*> que;
			que.push(rootNode);
			while (que.size() > 0)
			{
				aiNode* node = que.front();
				que.pop();
				if (node->mName == name) return node;
				for (int i = 0; i < node->mNumChildren; ++i)
				{
					que.push(node->mChildren[i]);
				}
			}
			return nullptr;
		}

		world::SkeletonPtr AssimpLoader::createSkeletonByRootBone(aiNode* rootNode)
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
				// set parent index. As we use hierachy first traverse, parent is inited before children and supposed to be found here
				joint.m_parentIndex = -1;
				aiNode* parent = node->mParent;
				if (parent)
				{
					auto parentName = node->mName.C_Str();
					for (int i = 0; i < joints.size(); ++i)
					{
						if (strcmp(parentName, joints[i].m_name.c_str()) == 0)
						{
							joint.m_parentIndex = i;
							break;
						}
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

		AssimpLoader::VertexSkinData::VertexSkinData(unsigned int jointIdx, float weight):
			jointIdx(jointIdx), weight(weight)
		{
		}

}
}

