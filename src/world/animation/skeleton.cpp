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
			m_aJoint = new Joint[jointCount];
			m_id = SkeletonManager::instance()->createSkeletonID();
		}
		Skeleton::~Skeleton()
		{
			delete[] m_aJoint;
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
		void JointPose::mix(const JointPose& srcPose, const JointPose& destPose, JointPose& outPose, float destFactor)
		{
			outPose.m_trans = math3d::mix(srcPose.m_trans, destPose.m_trans, destFactor);
			outPose.m_rot = math3d::mix(srcPose.m_rot, destPose.m_rot, destFactor);
			outPose.m_scale = math3d::mix(srcPose.m_scale, destPose.m_scale, destFactor);
		}
	}
}


#endif // !WATER_SKELETON_H
