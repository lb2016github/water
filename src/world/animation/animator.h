#ifndef WATER_ANIMATOR_H
#include "animation.h"
#include <map>
#include <string>
#include "common/timeline.h"



namespace water
{
	namespace world
	{
		class Animator
		{
		private:
			// animation data
			SkeletonAnimationClipDataPtr m_pSkelAnimClipData;
			// cur anim name
			std::string m_sCurAnim;
		public:
			void tick(float delta);
		};
		// helper of playing an animation
		class AnimationPlayHelper: TimelineObserver
		{
		public:
			AnimationPlayHelper();
			~AnimationPlayHelper();
		protected:
			virtual void on_time(float time);
			virtual void on_start();
			virtual void on_end();
			virtual void on_cancel();
		private:
			float pre_time = { -1 };
			std::vector<TimelineCallbackWrapper> m_callbacks;
			Timeline m_timeline;
		};
	}
}


#endif // !WATER_ANIMATOR_H
