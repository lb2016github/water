#include "animation.h"
#include "skeleton.h"


namespace water
{
	namespace world
	{
		AnimationSample::AnimationSample(unsigned int jointCount): m_jointCount(jointCount)
		{
			m_jointPose = new JointPose[jointCount];
		}
		AnimationSample::~AnimationSample()
		{
			delete[] m_jointPose;
		}
		void AnimationSample::mix(const AnimationSamplePtr srcSample, const AnimationSamplePtr dstSample, AnimationSamplePtr& outSample, const float& dstFactor)
		{
			assert(srcSample->m_jointCount == dstSample->m_jointCount);
			for (int i = 0; i < srcSample->m_jointCount; ++i)
			{
				JointPose::mix(srcSample->m_jointPose[i], dstSample->m_jointPose[i], outSample->m_jointPose[i], dstFactor);
			}
		}
		AnimationClip::AnimationClip(SkeletonPtr skPtr, unsigned int sampleCount):
			m_skeleton(skPtr), m_sampleCount(sampleCount)
		{
			m_animSample = new AnimationSamplePtr[sampleCount];
			m_timeMic = new unsigned int[sampleCount];
		}
		AnimationClip::~AnimationClip()
		{
			delete[] m_animSample;
			delete[] m_timeMic;
		}
		AnimationSamplePtr AnimationClip::getSample(float timeMic)
		{
			if (timeMic < 0)
			{
				return m_animSample[0];
			}
			else if (timeMic > m_timeMic[m_sampleCount - 1])
			{
				return m_animSample[m_sampleCount - 1];
			}
			AnimationSamplePtr beforeSamplePtr{ nullptr }, afterSamplePtr{ nullptr };
			float beforeTime{ 0 }, afterTime{ 0 };
			for (int i = 0; i < m_skeleton->m_jointCount; ++i)
			{
				if (m_timeMic[i] <= timeMic)
				{
					beforeSamplePtr = m_animSample[i];
					beforeTime = m_timeMic[i];
				}
				else if(m_timeMic[i] >= timeMic)
				{
					afterSamplePtr = m_animSample[i];
					afterTime = m_timeMic[i];
				}
				if (beforeSamplePtr != nullptr && afterSamplePtr != nullptr)
				{
					break;
				}
			}
			float factor = (timeMic - beforeTime) / (afterTime - beforeTime);
			AnimationSamplePtr outSample = std::make_shared<AnimationSample>(m_skeleton->m_jointCount);
			AnimationSample::mix(beforeSamplePtr, afterSamplePtr, outSample, factor);
			return outSample;
		}
		float AnimationClip::getDuration()
		{
			return m_timeMic[m_sampleCount - 1];
		}
		AnimationClipManager* AnimationClipManager::instance()
		{
			static AnimationClipManager instance;
			return &instance;
		}
		AnimationClipData::AnimationClipData()
		{
		}
		AnimationClipPtr AnimationClipData::getAnimClip(const std::string& animName)
		{
			auto rst = m_animClipData.find(animName);
			if (rst == m_animClipData.end())
			{
				return nullptr;
			}
			return rst->second;
		}
	}
}
