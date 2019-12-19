#ifndef WATER_SKELETON_H
#include <string>
#include <vector>
#include "math3d/math3d.hpp"
#include "common/common.h"

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
			SkeletonID m_id;				// id of skeleton
			unsigned int m_jointCount;	// count of joints
			Joint* m_aJoint;			// array of joints
		};

		struct JointPose
		{
			math3d::Vector3 m_trans;
			math3d::Vector3 m_scale;
			math3d::Quaternion m_rot;
		};
		struct SkeletonPose
		{
			Skeleton* m_skeleton;
			JointPose* m_aJointPose;	//array of joint pose
		};
	}
}


#endif // !WATER_SKELETON_H
