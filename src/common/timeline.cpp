#include "timeline.h"


namespace water
{
	void Timeline::tick(float delta_time)
	{
		if (!m_started)
		{
			m_started = true;
			on_start();
		}
		// trigger start 
		m_time += delta_time;
		// 1. trigger callbacks
		while (true)
		{
			auto top = m_callbacks.top();
			if (top.m_time <= m_time)
			{
				// trigger
				top.m_callback();
				m_callbacks.pop();
			}
			else
			{
				break;
			}
		}
		// check if timeline is end
		if (m_time >= m_duration)
		{
			on_end();
		}
	}
	void Timeline::on_start()
	{
	}
	void Timeline::on_end()
	{
	}
	CallbackHandler Timeline::register_callback(float time, TimelineCallback cb)
	{
		TimelineCallbackWrapper tcw(time, cb);
		m_callbacks.push(tcw);
	}
	CallbackHandler Timeline::register_start_callback(TimelineCallback cb)
	{
		register_callback(0, cb);
	}
	CallbackHandler Timeline::register_end_callback(TimelineCallback cb)
	{
		register_callback(m_duration, cb);
	}
	void Timeline::unregister_callback(CallbackHandler handler)
	{
		m_callbacks.erase(handler);
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
