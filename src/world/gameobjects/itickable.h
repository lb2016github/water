#pragma once
#include "common/common.h"

namespace water
{
	namespace world
	{
		class ITickable
		{
		public:
			ITickable() : m_tickEnable(true) {}
			ITickable(bool tickEnable) : m_tickEnable(tickEnable) {}
		public:
			/*
			tick function
			@param deltaTimeMic: delta time, note that time is in microsecond
			*/
			virtual void tick(float deltaTimeMic) = 0;

			bool inline isTickEnable() { return m_tickEnable; }
			void setTickEnable(bool enable) { m_tickEnable = enable; }
		public:
			/* mark whether tick is enable */
			bool m_tickEnable;
		};
	}
}