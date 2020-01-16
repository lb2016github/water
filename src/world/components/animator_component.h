#ifndef WATER_ANIMATOR_COMPONENT_H
#define WATER_ANIMATOR_COMPONENT_H

#include "base_component.h"
#include <string>
#include "world/animation/animator.h"
#include "world/animation/animation.h"

namespace water
{
	namespace world
	{
		class AnimatorComponent : public BaseComponent
		{
		public:
			using BaseComponent::BaseComponent;
			static const ComponentTag tag = COMP_ANIMATOR;
		public:
			void initAnimationClipData(AnimationClipDataPtr animClipDataPtr);
			Animator* getAnimator();
			SkeletonPosePtr getCurPose();

		public:
			Animator* m_animator{ nullptr };

		};
	}
}

#endif // !WATER_ANIMATOR_COMPONENT_H
