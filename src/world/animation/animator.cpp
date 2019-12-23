#include "animator.h"
#include "common/log.h"


namespace water
{
	namespace world
	{
		Animator::Animator(AnimationClipDataPtr clipData):
			m_animClipData(clipData)
		{
		}
		void Animator::playAnim(std::string animName, bool loop)
		{
			log_info("[Anim]Play anim %s", animName.c_str());
			if (m_curAnimName == animName && m_curAnimTimeline != nullptr)
			{
				m_curAnimTimeline->setLoop(loop);
				m_curAnimTimeline->replay();
				return;
			}
			AnimationClipPtr animClip = m_animClipData->getAnimClip(animName);
			if (animClip == nullptr)
			{
				log_error("[Anim]Anim name %s is not found", animName.c_str());
				return;
			}
			SAFE_DELETE(m_curAnimTimeline);
			m_curAnimName = animName;
			m_curAnimTimeline = new AnimationTimeline(animClip, loop);
		}
		AnimationTimeline* Animator::getAnimTimeline()
		{
			return m_curAnimTimeline;
		}
		AnimationTimeline::AnimationTimeline(AnimationClipPtr animClip, bool loop):
			Timeline(animClip->getDuration(), loop), m_animClip(animClip)
		{
			m_curAnimSample = m_animClip->getSample(m_curTime);
			addObserver(this);
		}
		void AnimationTimeline::onTime(float curTime)
		{
			m_curAnimSample = m_animClip->getSample(curTime);
		}
	}
}
