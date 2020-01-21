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
			/*
			init animation clip data
			*/
			void initAnimationClipData(AnimationClipDataPtr animClipDataPtr);

			/*
			play animation
			@param animName: name of animation
			@param loop: whether current animation is loop
			*/
			void playAnim(std::string animName, bool loop = false);

			SkeletonPosePtr getCurPose();

			virtual void tick(float timeMic);

		public:
			// animation data
			AnimationClipDataPtr m_animClipData;
			// cur anim name
			std::string m_curAnimName{ "" };
			// timeline of animation
			AnimationTimeline* m_curAnimTimeline{ nullptr };

		};
	}
}

#endif // !WATER_ANIMATOR_COMPONENT_H
