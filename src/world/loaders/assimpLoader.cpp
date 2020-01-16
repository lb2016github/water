#include "assimpLoader.h"
#include "filesystem/filesystem.h"
#include "assimp/postprocess.h"
#include "common/log.h"
#include <set>
#include <queue>
#include <map>
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
			printf("================= START ROOTNODE\n");
			printNode(m_scene->mRootNode, 0);
			printf("================= END ROOTNODE\n");
			// load skeleton and animation
			loadSkeleton();
			loadAnimation();
			loadSkinData();
			loadMesh();
		}

		render::MeshDataPtr AssimpLoader::getCombinedMesh()
		{
			if (m_combinedMeshPtr) return m_combinedMeshPtr;
			m_combinedMeshPtr = render::MeshData::combineMeshes(m_meshList);
			return m_combinedMeshPtr;
		}

		std::vector<render::MeshDataPtr> AssimpLoader::getAllMesh()
		{
			return m_meshList;
		}

		void AssimpLoader::loadSkeleton()
		{
			if (!m_scene->HasAnimations()) return;
			// find all affected nodes
			std::set<std::string> nodeNames;
			for (int i = 0; i < m_scene->mNumAnimations; ++i)
			{
				auto anim = m_scene->mAnimations[i];
				for (int j = 0; j < anim->mNumChannels; ++j)
				{
					nodeNames.emplace(anim->mChannels[j]->mNodeName.C_Str());
				}
			}
			// construct map{nodeName: subRootNode*}
			std::map<std::string, aiNode*> subRootNodeMap;
			auto rootNode = m_scene->mRootNode;
			for (int i = 0; i < rootNode->mNumChildren; ++i)
			{
				auto subRootNode = rootNode->mChildren[i];
				// traverse subRootNode, and construct subRootNodeMap
				std::queue<aiNode*> nodes;
				nodes.emplace(subRootNode);
				while (nodes.size() > 0)
				{
					auto cur = nodes.front();
					subRootNodeMap[cur->mName.C_Str()] = subRootNode;
					nodes.pop();
					for (int k = 0; k < cur->mNumChildren; ++k)
					{
						nodes.emplace(cur->mChildren[k]);
					}
				}
			}
			// find all affected children of RootNode
			std::set<aiNode*> animSubRootNodes;
			for each (auto name in nodeNames)
			{
				auto rst = subRootNodeMap.find(name);
				assert(rst != subRootNodeMap.end());
				animSubRootNodes.emplace(rst->second);
			}
			// load skeletons
			auto filterNode = [&animSubRootNodes](aiNode* node)->bool
			{
				return animSubRootNodes.find(node) != animSubRootNodes.end();
			};
			m_skPtr = createSkeletonByRootBone(m_scene, filterNode);
			m_skPtr = SkeletonManager::instance()->addSkeleton(m_skPtr);
		}

		void AssimpLoader::loadAnimation()
		{
			for (int i = 0; i < m_scene->mNumAnimations; ++i)
			{
				std::set<std::string> bones;
				auto anim = m_scene->mAnimations[i];
				assert(anim->mNumChannels > 0);

				world::AnimationClipPtr anim_clip_ptr = std::make_shared<world::AnimationClip>(m_skPtr, anim->mDuration);
				// for every bone
				for (int j = 0; j < anim->mNumChannels; ++j)
				{
					auto nodeAnim = anim->mChannels[j];
					auto boneName = nodeAnim->mNodeName;
					bones.emplace(boneName.C_Str());
					auto idx = m_skPtr->getJointIndexByName(boneName.C_Str());
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
				world::AnimationClipManager::instance()->getAnimClipDataPtr(m_skPtr->m_id)->addAnimClip(anim->mName.C_Str(), anim_clip_ptr);
			printf("============================= Anim bones %sStart\n", anim->mName.C_Str());
			for each (auto name in bones)
			{
				printf("%s\n", name.c_str());
			}
			printf("============================= Anim bones End\n");
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
				// save skin data
				for (int j = 0; j < mesh->mNumBones; ++j)
				{
					aiBone* bone = mesh->mBones[j];
					printf("%s\n", bone->mName.C_Str());
					unsigned int jointIdx = m_skPtr->getJointIndexByName(bone->mName.C_Str());
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
				if (parent == m_scene->mRootNode) return node;
				else node = parent;
				//std::string pName = parent->mName.C_Str();
				//// parent name starts with child name and contains Assimp
				//if (pName.find(node->mName.C_Str()) == 0 && pName == "RootNode")
				//{
				//	return node;
				//}
				//else
				//{
				//	node = parent;
				//}
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

		world::SkeletonPtr AssimpLoader::createSkeletonByRootBone(const aiScene* scene, std::function<bool(aiNode*)> filter)
		{
			// hierachy first traverse
			std::queue<aiNode*> nodes;
			nodes.push(scene->mRootNode);

			// 2. load invBindMatrix, MARK: we suppose meshes has same bind pose
			std::map<std::string, math3d::Matrix> inverseMatrixMap;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				auto mesh = scene->mMeshes[i];
				for (int j = 0; j < mesh->mNumBones; ++j)
				{
					auto bone = mesh->mBones[j];
					auto invMtx = bone->mOffsetMatrix;
					math3d::Matrix curMtx(
						invMtx.a1, invMtx.a2, invMtx.a3, invMtx.a4,
						invMtx.b1, invMtx.b2, invMtx.b3, invMtx.b4,
						invMtx.c1, invMtx.c2, invMtx.c3, invMtx.c4,
						invMtx.d1, invMtx.d2, invMtx.d3, invMtx.d4
					);
					auto rst = inverseMatrixMap.find(bone->mName.C_Str());
					if (rst != inverseMatrixMap.end())
					{
						auto preMtx = rst->second;
						// check invMtx is same
						auto diff = preMtx - curMtx;
						auto sum = diff.m11 + diff.m12 + diff.m13 + diff.m14 +
							diff.m21 + diff.m22 + diff.m23 + diff.m24 +
							diff.m31 + diff.m32 + diff.m33 + diff.m34 +
							diff.m41 + diff.m42 + diff.m43 + diff.m44;
						assert(sum < 0.1);
					}
					else
					{
						inverseMatrixMap[bone->mName.C_Str()] = curMtx;
					}
				}
			}

			// save nodes
			std::vector<world::Joint> joints;
			while (nodes.size() > 0)
			{
				aiNode* node = nodes.front();
				nodes.pop();
				// create Joint with aiNode
				world::Joint joint;
				joint.m_name = node->mName.C_Str();
				joint.m_parentIndex = -1;
				// set parent index. As we use hierachy first traverse, parent is inited before children and supposed to be found here
				auto parent = node->mParent;
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
				// load invBindMatrix
				auto tmp = inverseMatrixMap.find(joint.m_name);
				if (tmp == inverseMatrixMap.end())
				{
					if (joint.m_parentIndex >= 0)
					{
						joint.m_invBindPose = joints[joint.m_parentIndex].m_invBindPose;
					}
					else
					{
						joint.m_invBindPose.identity();
					}
				}
				else
				{
					joint.m_invBindPose = tmp->second;
				}

				joints.push_back(joint);

				// add children to nodes
				for (int i = 0; i < node->mNumChildren; ++i)
				{
					auto child = node->mChildren[i];
					if (filter(child))
					{
						nodes.push(child);
					}
				}
			}
			SkeletonPtr skPtr = std::make_shared<Skeleton>(joints.size());
			memcpy(skPtr->m_joints, joints.data(), sizeof(Joint) * skPtr->m_jointCount);
			return skPtr;
		}

		AssimpLoader::VertexSkinData::VertexSkinData(unsigned int jointIdx, float weight):
			jointIdx(jointIdx), weight(weight)
		{
		}

}
}

