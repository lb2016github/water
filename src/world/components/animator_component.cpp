#include "animator_component.h"
#include "component_const.h"
#include "world/gameobjects/component_object.hpp"
#include "filesystem/filesystem.h"

namespace water
{
	namespace world
	{
		REGISTER_COMPONENT(AnimatorComponent, GameObject);

		void AnimatorComponent::initAnimationClipData(AnimationClipDataPtr animClipDataPtr)
		{
			SAFE_DELETE(m_animator);
			m_animator = new Animator(animClipDataPtr);
			if (!animClipDataPtr->isEmpty())
			{
				m_animator->playAnim(animClipDataPtr->m_defaultClipName, true);
			}
		}

		Animator* AnimatorComponent::getAnimator()
		{
			return m_animator;
		}

		SkeletonPosePtr AnimatorComponent::getCurPose()
		{
			if (!m_animator) return nullptr;
			return m_animator->getAnimTimeline()->getCurPose();
		}

	}
}
