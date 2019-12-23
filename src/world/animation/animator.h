#ifndef WATER_ANIMATOR_H
#define WATER_ANIMATOR_H
#include "animation.h"
#include <map>
#include <string>
#include "common/timeline.h"



namespace water
{
	namespace world
	{
		/*
		Animator of a model
		*/
		class Animator
		{
		public:
			Animator(AnimationClipDataPtr clipData);
			/*
			play animation
			@param animName: name of animation
			@param loop: whether current animation is loop
			*/
			void playAnim(std::string animName, bool loop = false);
			AnimationTimeline* getAnimTimeline();
		private:
			// animation data
			AnimationClipDataPtr m_animClipData;
			// cur anim name
			std::string m_curAnimName{ "" };
			// timeline of animation
			AnimationTimeline* m_curAnimTimeline{ nullptr };
		};

		/*
		implementation of updating animation
		*/
		class AnimationTimeline : public Timeline, public TimelineObserver
		{
		public:
			AnimationTimeline(AnimationClipPtr animClip, bool loop);
		private:
			AnimationSamplePtr m_curAnimSample{ nullptr };
			AnimationClipPtr m_animClip{ nullptr };
		protected:
			void onTime(float curTime);
		};


	}
}


#endif // !WATER_ANIMATOR_H
