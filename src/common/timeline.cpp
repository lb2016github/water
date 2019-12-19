#include "timeline.h"


namespace water
{
	void Timeline::tick(float delta_time)
	{
		delta_time = m_ratio * delta_time;
		// check pause state
		if (!m_started || m_paused || m_ended)
		{
			return;
		}
		// trigger start 
		m_time += delta_time;
		// check if timeline is end
		if (m_time >= m_duration)
		{
			for each (auto observer in m_observer_set)
			{
				observer->on_time(m_duration);
			}

			if (m_loop)
			{
				m_time -= m_duration;
			}
			else
			{
				m_ended = true;
				for each (auto observer in m_observer_set)
				{
					observer->on_end();
				}
			}
		}
		else
		{
			for each (auto observer in m_observer_set)
			{
				observer->on_time(m_duration);
			}
		}
	}
	void Timeline::pause()
	{
		m_paused = true;
	}
	void Timeline::resume()
	{
		m_paused = false;
	}
	void Timeline::start()
	{
		if (m_started)
		{
			return;
		}
		m_started = true;
		for each (auto observer in m_observer_set)
		{
			observer->on_start();
		}
	}
	void Timeline::stop()
	{
		m_ended = true;
		for each (auto observer in m_observer_set)
		{
			observer->on_cancel();
		}
		
	}
	void Timeline::set_ratio(float ratio)
	{
		m_ratio = ratio;
	}
	void Timeline::add_observer(TimelineObserver* observer)
	{
		auto iter = m_observer_set.find(observer);
		if (iter == m_observer_set.end())
		{
			m_observer_set.emplace(observer);
		}
	}
	void Timeline::remove_observer(TimelineObserver* observer)
	{
		auto iter = m_observer_set.find(observer);
		if (iter != m_observer_set.end())
		{
			m_observer_set.erase(iter);
		}
	}
	TimelineCallbackWrapper::TimelineCallbackWrapper(float time, TimelineCallback cb): m_time(time), m_callback(cb)
	{
		m_handler = get_handler();
	}
	TimelineCallbackWrapper::TimelineCallbackWrapper(CallbackHandler handler): m_handler(handler)
	{
	}
	TimelineCallbackWrapper::TimelineCallbackWrapper(const TimelineCallbackWrapper& tcw):
		m_time(tcw.m_time), m_handler(tcw.m_handler), m_callback(tcw.m_callback)
	{
	}
	bool TimelineCallbackWrapper::operator<(const TimelineCallbackWrapper& tcw)
	{
		return m_time < tcw.m_time;
	}
	bool TimelineCallbackWrapper::operator==(const TimelineCallbackWrapper& tcw)
	{
		return m_handler == tcw.m_handler || (m_time == tcw.m_time && m_callback == tcw.m_callback);
	}
	CallbackHandler TimelineCallbackWrapper::get_handler()
	{
		static CallbackHandler handler = 0;
		return ++handler;
	}
}
