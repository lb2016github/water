#ifndef WATER_ANIMATION_H
#include "math3d/math3d.hpp"
#include "skeleton.h"
#include <map>

namespace water
{
	namespace world
	{
		struct AnimationSample
		{
			JointPose* m_aJointPose;
		};

		struct AnimationClip
		{
			SkeletonID m_idSkeleton;		// id of skeleton
			AnimationSample* m_aAnimSample;
			unsigned int* m_aTimeMic;		// time in micsecond of samples
			unsigned int m_sampleCount;		// count of samples
		};
	}
}

#endif // !WATER_ANIMATION_H
