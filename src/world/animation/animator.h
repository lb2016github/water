#ifndef WATER_ANIMATOR_H
#include "animation.h"
#include <map>
#include <string>
#include "common/timeline.h"



namespace water
{
	namespace world
	{
		class TimelineAnimator: public Timeline
		{
		private:
			// animation data
			SkeletonAnimationClipDataPtr m_pSkelAnimClipData;
			// cur anim name
			std::string m_sCurAnim;
		};
	}
}


#endif // !WATER_ANIMATOR_H
