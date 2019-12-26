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
			Joint();
			std::string m_name {""};				// name of joint
			math3d::Matrix m_invBindPose;	// inverse of bind pose
			int m_parentIndex{ -1 };		// index of parent joint
		};

		struct Skeleton: public std::enable_shared_from_this<Skeleton>

		{
			Skeleton(unsigned int jointCount);
			~Skeleton();
			SkeletonID m_id;				// id of skeleton
			unsigned int m_jointCount;	// count of joints
			Joint* m_joints;			// array of joints
		};
		DECL_SHARED_PTR(Skeleton);

		struct JointPose
		{
			JointPose();
			JointPose(const math3d::Vector3& trans, const math3d::Vector3& scale, const math3d::Quaternion& rot);
			math3d::Vector3 m_trans;
			math3d::Vector3 m_scale;
			math3d::Quaternion m_rot;

			static void mix(const JointPose& srcPose, const JointPose& destPose, JointPose& outPose, float destFactor);
		};
		struct SkeletonPose: public std::enable_shared_from_this<SkeletonPose>
		{
			SkeletonPose(SkeletonPtr skePtr);
			~SkeletonPose();
			SkeletonPtr m_skeleton;
			JointPose* m_jointPoses;	//array of joint pose
		};
		DECL_SHARED_PTR(SkeletonPose);
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
