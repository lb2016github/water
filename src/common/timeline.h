#ifndef WATER_TIMELINE_H
#include <list>
#include "adt.hpp"
#include <set>
#include "common.h"


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

	WaterInterface TimelineObserver
	{
		virtual void on_time(float time) = 0;
		virtual void on_start() = 0;
		virtual void on_end() = 0;
		virtual void on_cancel() = 0;
	};

	class Timeline
	{
	protected:
		// duration and current time
		float m_duration{ 0 };
		float m_time{ 0 };
		float m_ratio{ 1.0 };	// ratio of timeline
		bool m_loop{ false };
		// tag of status
		bool m_paused{ false };
		bool m_started{ false };
		bool m_ended{ false };
		// observers
		std::set<TimelineObserver*> m_observer_set;

	public:
		void start();
		void stop();
		void pause();
		void resume();
		
		// users should call tick
		void tick(float delta_time);
		void set_ratio(float ratio);
		void add_observer(TimelineObserver* observer);
		void remove_observer(TimelineObserver* observer);
	};
}

#endif // !WATER_TIMELINE_H
