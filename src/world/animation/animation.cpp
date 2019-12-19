#include "animation.h"


namespace water
{
	namespace world
	{
		AnimationSample::~AnimationSample()
		{
			delete[] m_aJointPose;
		}
		AnimationClip::AnimationClip(SkeletonID skeletonId, unsigned int sampleCount):
			m_idSkeleton(skeletonId), m_sampleCount(sampleCount)
		{
			m_aAnimSample = new AnimationSample[sampleCount];
			m_aTimeMic = new unsigned int[sampleCount];
		}
		AnimationClip::~AnimationClip()
		{
			delete[] m_aAnimSample;
			delete[] m_aTimeMic;
		}
		AnimationClipManager* AnimationClipManager::instance()
		{
			static AnimationClipManager instance;
			return &instance;
		}
	}
}
