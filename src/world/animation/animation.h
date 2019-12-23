#ifndef WATER_ANIMATION_H
#define WATER_ANIMATION_H
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
		struct AnimationSample: std::enable_shared_from_this<AnimationSample>
		{
			AnimationSample(unsigned int jointCount);
			~AnimationSample();

			/*
			array of JointPose, which saves joint pose data
			*/
			JointPose* m_jointPose{ nullptr };
			/*
			joint count
			*/
			unsigned int m_jointCount;

			/*
			mix two samples
			*/
			static void mix(const AnimationSamplePtr srcSample, const AnimationSamplePtr dstSample, AnimationSamplePtr& outSample, const float& dstFactor);
		};
		DECL_SHARED_PTR(AnimationSample);

		/*
		data of one animation clip
		*/
		class AnimationClip: std::enable_shared_from_this<AnimationClip>
		{
		public:
			AnimationClip(SkeletonPtr skPtr, unsigned int sampleCount);
			~AnimationClip();
		public:
			/*
			get before sample and after sample with given time(in microsecond).
			With the before and after samples, joint poses can be interpola
			*/
			AnimationSamplePtr getSample(float timeMic);
			/*
			get duration of animation clip
			@return time/microsecond
			*/
			float getDuration();
		private:
			SkeletonPtr m_skeleton;		// id of skeleton
			AnimationSamplePtr* m_animSample;
			unsigned int* m_timeMic;		// time in micsecond of samples
			unsigned int m_sampleCount;		// count of samples
		};

		DECL_SHARED_PTR(AnimationClip);

		/*
		animation clip data of one skeleton
		*/
		struct AnimationClipData
		{
			AnimationClipData();
			AnimationClipPtr getAnimClip(const std::string& animName);

			std::map<std::string, AnimationClipPtr> m_animClipData;
			std::string m_defaultClipName;
		};
		DECL_SHARED_PTR(AnimationClipData);

		/*
		Manager of animation clip
		*/
		class AnimationClipManager
		{
		private:
			std::map<SkeletonID, AnimationClipDataPtr> m_skeletonAnimClipData;
		public:
			static AnimationClipManager* instance();
		};
	}
}

#endif // !WATER_ANIMATION_H
