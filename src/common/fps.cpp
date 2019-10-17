#include "fps.h"
#include <time.h>

namespace water
{
	FramePerSecond::FramePerSecond()
	{
		m_update_time = clock() + CLOCKS_PER_SEC;
	}
	void FramePerSecond::on_frame()
	{
		m_frame_cnt += 1;
		float current = clock();
		if (m_update_time <= current)
		{
			m_fps = m_frame_cnt;
			m_update_time = current + CLOCKS_PER_SEC;
			m_frame_cnt = 0;
		}
	}
}
