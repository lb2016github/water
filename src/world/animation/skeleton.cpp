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
		SkeletonPtr SkeletonManager::getSkeleton(SkeletonID skeId)
		{
			auto iter = m_mSkeleton.find(skeId);
			if (iter == m_mSkeleton.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		void SkeletonManager::addSkeleton(SkeletonPtr skeletonPtr)
		{
			m_mSkeleton[skeletonPtr->m_id] = skeletonPtr;
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
		SkeletonPose::SkeletonPose(SkeletonPtr skePtr):
			m_skeleton(skePtr)
		{
			m_jointPoses = new JointPose[skePtr->m_jointCount];
		}
		SkeletonPose::~SkeletonPose()
		{
			delete[] m_jointPoses;
		}
	}
}


#endif // !WATER_SKELETON_H
