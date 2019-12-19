#include "animator.h"

water::world::AnimationPlayHelper::AnimationPlayHelper()
{
	add_observer(this);
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
