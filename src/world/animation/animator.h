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
		/*
		helper of playing an animation
		*/
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
		public:
			// base control
			void start();
			void stop();
			void pause();
			void resume();
			// users should call tick
			void tick(float delta_time);
			void set_ratio(float ratio);
			// callbacks
			void register_anim_callback(float time, TimelineCallback cb);
			void register_start_callback(TimelineCallback cb);
			void register_end_callback(TimelineCallback cb);

		private:
			float pre_time = { -1 };
			std::vector<TimelineCallbackWrapper> m_callbacks;
			Timeline m_timeline;
		};
	}
}

class Tree {
public:
	Tree* lChild;
	Tree* rChild;
};

bool isSubTree(Tree child, Tree root)
{
	if (child == root) return true;
	if (isSubTree(child, root->lCHild)) return true;
	if (isSubTree(child, root->rChild)) return true;
	return false;
	
}

#endif // !WATER_ANIMATOR_H
