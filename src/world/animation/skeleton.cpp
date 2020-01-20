#ifndef WATER_SKELETON_H
#include <string>
#include <vector>
#include "math3d/math3d.hpp"
#include "common/common.h"
#include "skeleton.h"
#include "common/util.h"

namespace water
{
	namespace world
	{
		Skeleton::Skeleton(unsigned int jointCount):
			m_jointCount(jointCount)
		{
			m_joints = new Joint[jointCount];
			m_id = SkeletonManager::instance()->createSkeletonID();
		}
		Skeleton::~Skeleton()
		{
			delete[] m_joints;
		}

		int Skeleton::getJointIndexByName(std::string name)
		{
			for (int i = 0; i < m_jointCount; ++i)
			{
				if (m_joints[i].m_name == name) return i;
			}
			return -1;
		}
		bool Skeleton::equals(const SkeletonPtr skePtr)
		{
			if (m_jointCount != skePtr->m_jointCount) return false;
			for (int i = 0; i < m_jointCount; ++i)
			{
				// only check join structor
				auto joint1 = m_joints[i];
				auto joint2 = skePtr->m_joints[i];
				if (joint1.m_parentIndex != joint2.m_parentIndex)
				{
					return false;
				}
			}
			return true;
		}
		SkeletonPtr SkeletonManager::getSkeleton(SkeletonID skeId)
		{
			auto iter = m_mSkeleton.find(skeId);
			if (iter == m_mSkeleton.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		SkeletonPtr SkeletonManager::addSkeleton(SkeletonPtr skeletonPtr)
		{
			for (auto iter = m_mSkeleton.begin(); iter != m_mSkeleton.end(); ++iter)
			{
				if (iter->second->equals(skeletonPtr))
				{
					return iter->second;
				}
			}
			m_mSkeleton[skeletonPtr->m_id] = skeletonPtr;
			return skeletonPtr;
		}
		SkeletonID SkeletonManager::createSkeletonID()
		{
			return create_id();
		}
		SkeletonManager* SkeletonManager::instance()
		{
			static SkeletonManager skMgr;
			return &skMgr;
		}
		JointPose::JointPose()
		{
			m_trans = math3d::Vector3(0, 0, 0);
			m_scale = math3d::Vector3(1, 1, 1);
			m_rot = math3d::Quaternion::identity();
		}
		JointPose::JointPose(const math3d::Vector3& trans, const math3d::Vector3& scale, const math3d::Quaternion& rot):
			m_trans(trans), m_scale(scale), m_rot(rot)
		{
		}
		void JointPose::lerp(const JointPose& srcPose, const JointPose& destPose, JointPose& outPose, float destFactor)
		{
			outPose.m_trans = math3d::Vector3::lerp(srcPose.m_trans, destPose.m_trans, destFactor);
			outPose.m_rot = math3d::Quaternion::slerp(srcPose.m_rot, destPose.m_rot, destFactor);
			outPose.m_scale = math3d::Vector3::lerp(srcPose.m_scale, destPose.m_scale, destFactor);
		}
		Joint::Joint()
		{
			m_invBindPose = math3d::Matrix::makeIdentityMatrix();
		}
		Joint& Joint::operator=(const Joint& joint)
		{
			if (this == &joint) return *this;
			m_name = joint.m_name;
			m_invBindPose = joint.m_invBindPose;
			m_parentIndex = joint.m_parentIndex;
			return *this;
		}
		bool Joint::operator==(const Joint& joint)
		{
			if (this == &joint) return true;
			if (m_name != joint.m_name) return false;
			if (m_parentIndex != joint.m_parentIndex) return false;
			if (m_invBindPose != joint.m_invBindPose) return false;
			return true;
		}
		bool Joint::operator!=(const Joint& joint)
		{
			return !operator==(joint);
		}
		SkeletonPose::SkeletonPose(SkeletonPtr skePtr):
			m_skeleton(skePtr)
		{
			m_jointPoses = new JointPose[skePtr->m_jointCount];
		}
		SkeletonPose::~SkeletonPose()
		{
			delete[] m_jointPoses;
		}
		void SkeletonPose::initSkinMatrix()
		{
			std::vector<math3d::Matrix> gJointPose;
			for (int i = 0; i < m_skeleton->m_jointCount; ++i)
			{
				Joint& joint = m_skeleton->m_joints[i];
				math3d::Matrix& invMatrix = joint.m_invBindPose;
				unsigned int parentIndex = joint.m_parentIndex;
				JointPose& jointPose = m_jointPoses[i];
				math3d::Matrix local = math3d::Matrix::makeMatrix(jointPose.m_scale, jointPose.m_rot, jointPose.m_trans);
				if (parentIndex > 0)
				{
					math3d::Matrix& parentPose = gJointPose[parentIndex];
					gJointPose[i] = parentPose * local;
				}
				else
				{
					gJointPose[i] = local;
				}
				m_skinMatrices.push_back(gJointPose[i] * invMatrix);
			}
		}
	}
}


#endif // !WATER_SKELETON_H
