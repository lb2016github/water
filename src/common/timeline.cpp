#include "timeline.h"
#include <math.h>

namespace water
{
	Timeline::Timeline(float duration): m_duration(duration), m_playing(true)
	{
	}

	Timeline::Timeline(float duration, bool loop):
		m_duration(duration), m_loop(loop), m_playing(true)
	{
	}

	Timeline::Timeline(float duration, bool loop, float speedRate):
		m_duration(duration), m_loop(loop), m_speedRate(speedRate), m_playing(true)
	{
	}

	Timeline::~Timeline()
	{
		m_sObserver.clear();
	}

	void Timeline::onTick()
	{
	}

	void Timeline::play()
	{
		m_playing = true;
	}

	void Timeline::replay()
	{
		m_curTime = 0;
		m_playing = true;
	}

	void Timeline::pause()
	{
		m_playing = false;
	}

	void Timeline::tick(float deltaTime)
	{
		if (!m_playing)
		{
			return;
		}
		// update current time
		m_curTime += m_speedRate * deltaTime;

		// inform observers
		if (m_curTime < 0)
		{
			_informTime(0);
		}
		else if (m_duration >= 0 && m_curTime > m_duration)
		{
			_informTime(m_duration);
		}
		else
		{
			_informTime(m_curTime);
		}

		// update current time when it is out of range
		if (m_curTime < 0)
		{
			if (m_loop && m_duration >= 0)
			{
				m_curTime += m_duration;
			}
			else
			{
				m_playing = false;
			}
		}
		else if (m_duration >= 0 && m_curTime > m_duration)
		{
			if (m_loop)
			{
				m_curTime -= m_duration;
			}
			else
			{
				m_playing = false;
			}
		}
		onTick();
	}

	float Timeline::getCurrentTime()
	{
		return m_curTime;
	}

	void Timeline::setCurrentTime(float time)
	{
		m_curTime = time;
	}

	void Timeline::setCurrentTimeRatio(float timeRatio)
	{
		if (m_duration < 0)
		{
			// duration is infinate
			return;
		}
		m_curTime = timeRatio * m_duration;
	}

	void Timeline::setLoop(bool loop)
	{
		m_loop = loop;
	}

	void Timeline::addObserver(TimelineObserver* obs)
	{
		m_sObserver.emplace(obs);
	}

	void Timeline::removeObserver(TimelineObserver* obs)
	{
		auto iter = m_sObserver.find(obs);
		if (iter != m_sObserver.end())
		{
			m_sObserver.erase(iter);
		}
	}

	void Timeline::setSpeedRate(float speedRate)
	{
		m_speedRate = speedRate;
	}

	float Timeline::getSpeedRate()
	{
		return m_speedRate;
	}

	void Timeline::_informTime(float time)
	{
		for each (auto obs in m_sObserver)
		{
			obs->onTime(time);
		}
	}
}

