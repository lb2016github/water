#ifndef WATER_ANIMATION_H
#include "math3d/math3d.hpp"
#include "skeleton.h"
#include <map>
#include "common/common.h"

namespace water
{
	namespace world
	{
		/*
		data of one animation sample
		*/
		struct AnimationSample
		{
			JointPose* m_aJointPose{ nullptr };
			~AnimationSample();
		};

		/*
		data of one animation clip
		*/
		class AnimationClip: std::enable_shared_from_this<AnimationClip>
		{
		public:
			AnimationClip(SkeletonID skeletonId, unsigned int sampleCount);
			~AnimationClip();
		private:
			SkeletonID m_idSkeleton;		// id of skeleton
			AnimationSample* m_aAnimSample;
			unsigned int* m_aTimeMic;		// time in micsecond of samples
			unsigned int m_sampleCount;		// count of samples
		};

		DECL_SHARED_PTR(AnimationClip);

		/*
		animation clip data of one skeleton
		*/
		struct SkeletonAnimationClipData
		{
			std::map<std::string, AnimationClipPtr> m_mAnimClipData;
		};
		DECL_SHARED_PTR(SkeletonAnimationClipData);

		/*
		Manager of animation clip
		*/
		class AnimationClipManager
		{
		private:
			std::map<SkeletonID, SkeletonAnimationClipDataPtr> m_mSkeletonAnimClipData;
		public:
			static AnimationClipManager* instance();
		};
	}
}

#endif // !WATER_ANIMATION_H
