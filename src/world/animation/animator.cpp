#include "animator.h"

water::world::AnimationPlayHelper::AnimationPlayHelper()
{
	m_timeline.add_observer(this);
}

water::world::AnimationPlayHelper::~AnimationPlayHelper()
{
}

void water::world::AnimationPlayHelper::on_time(float time)
{
	for each (auto cb in m_callbacks)
	{
		if (cb.m_time > pre_time&& cb.m_time <= time)
		{
			cb.m_callback();
		}
	}
}

void water::world::AnimationPlayHelper::on_start()
{
}

void water::world::AnimationPlayHelper::on_end()
{
}

void water::world::AnimationPlayHelper::on_cancel()
{
}

void water::world::AnimationPlayHelper::start()
{
	m_timeline.start();
}

void water::world::AnimationPlayHelper::stop()
{
	m_timeline.stop();
}

void water::world::AnimationPlayHelper::pause()
{
	m_timeline.pause();
}

void water::world::AnimationPlayHelper::resume()
{
	m_timeline.resume();
}

void water::world::AnimationPlayHelper::tick(float delta_time)
{
	m_timeline.tick(delta_time);
}

void water::world::AnimationPlayHelper::set_ratio(float ratio)
{
	m_timeline.set_ratio(ratio);
}
