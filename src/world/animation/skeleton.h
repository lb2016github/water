#ifndef WATER_SKELETON_H
#define WATER_SKELETON_H
#include <string>
#include <vector>
#include "math3d/math3d.hpp"
#include "common/common.h"
#include <map>

namespace water
{
	namespace world
	{
		typedef WATER_ID SkeletonID;
		struct Joint
		{
			std::string m_name;				// name of joint
			math3d::Matrix m_invBindPose;	// inverse of bind pose
			unsigned int m_parentIndex;		// index of parent joint
		};

		struct Skeleton
		{
			Skeleton(unsigned int jointCount);
			~Skeleton();
			SkeletonID m_id;				// id of skeleton
			unsigned int m_jointCount;	// count of joints
			Joint* m_aJoint;			// array of joints
		};
		DECL_SHARED_PTR(Skeleton);

		struct JointPose
		{
			math3d::Vector3 m_trans;
			math3d::Vector3 m_scale;
			math3d::Quaternion m_rot;

			static void mix(const JointPose& srcPose, const JointPose& destPose, JointPose& outPose, float destFactor);
		};
		struct SkeletonPose
		{
			SkeletonPtr m_skeleton;
			JointPose* m_aJointPose;	//array of joint pose
		};
		/*
		Manage skeletons
		*/
		class SkeletonManager
		{
		public:
			SkeletonPtr getSkeleton(SkeletonID skeId);
			void addSkeleton(SkeletonPtr skeletonPtr);
			static SkeletonID createSkeletonID();
			static SkeletonManager* instance();
		private:
			std::map<SkeletonID, SkeletonPtr> m_mSkeleton;
		};
	}
}


#endif // !WATER_SKELETON_H
