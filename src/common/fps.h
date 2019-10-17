#ifndef WATER_FPS_H
#define WATER_FPS_H

namespace water
{
	struct FramePerSecond
	{
		FramePerSecond();
		void on_frame();

		unsigned int m_fps{ 0 };
		float m_update_time{ 0 };
		unsigned int m_frame_cnt{ 0 };
	};
}
#endif // !WATER_FPS_H
