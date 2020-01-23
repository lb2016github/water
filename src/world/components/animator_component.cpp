#include "animator_component.h"
#include "component_const.h"
#include "world/gameobjects/component_object.hpp"
#include "filesystem/filesystem.h"
#include "common/log.h"

namespace water
{
	namespace world
	{
		REGISTER_COMPONENT(AnimatorComponent, GameObject);

		void AnimatorComponent::initAnimationClipData(AnimationClipDataPtr animClipDataPtr)
		{
			m_animClipData = animClipDataPtr;
			if (!m_animClipData->isEmpty())
			{
				m_tickEnable = true;
				playAnim(m_animClipData->m_defaultClipName, false);
			}
		}

		void AnimatorComponent::playAnim(std::string animName, bool loop)
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

		SkeletonPosePtr AnimatorComponent::getCurPose()
		{
			if (m_curAnimTimeline)
			{
				return m_curAnimTimeline->getCurPose();
			}
			return nullptr;
		}

		void AnimatorComponent::tick(float timeMic)
		{
			if (m_curAnimTimeline)
			{
				m_curAnimTimeline->tick(timeMic);
			}

		}

	}
}
