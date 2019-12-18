#ifndef WATER_TIMELINE_H
#include <list>
#include "adt.hpp"


namespace water
{
	typedef void(*TimelineCallback)();
	typedef unsigned int CallbackHandler;
	struct TimelineCallbackWrapper
	{
		float m_time{ -1 };
		TimelineCallback m_callback{ nullptr };
		CallbackHandler m_handler{ -1 };

		TimelineCallbackWrapper(float time, TimelineCallback cb);
		TimelineCallbackWrapper(CallbackHandler handler);
		TimelineCallbackWrapper(const TimelineCallbackWrapper& tcw);
		bool operator<(const TimelineCallbackWrapper& tcw);
		bool operator==(const TimelineCallbackWrapper& tcw);
	private:
		static CallbackHandler get_handler();
	};

	class Timeline
	{
	private:
		float m_duration{ 0 };
		float m_time{ 0 };
		bool m_started{ false };
		WaterPriorityQueue<TimelineCallbackWrapper> m_callbacks;
	protected:
		void tick(float delta_time);
		void virtual on_start();
		void virtual on_end();
	public:
		void start();
		CallbackHandler register_callback(float time, TimelineCallback cb);
		CallbackHandler register_start_callback(TimelineCallback cb);
		CallbackHandler register_end_callback(TimelineCallback cb);
		void unregister_callback(CallbackHandler handler);
	};
	class LoopTimeline
	{
		void virtual on_end();
	};
}

#endif // !WATER_TIMELINE_H
