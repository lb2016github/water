#include "render_thread.h"
#include "device.h"

namespace water
{
	namespace render
	{
		RenderThread::RenderThread()
		{
		}
		bool RenderThread::run()
		{
			if (!RenderTaskManager::get_instance()->is_front_ready())
			{
					return false;
			}
			get_device()->clear();
			// get buffer data
			RenderTaskManager::get_instance()->get_front_buffer(m_task_buffer);
			// todo sort tasks to decrease drawcall 
			// do render jobs
			for each (RenderTaskPtr task in m_task_buffer.m_tasks)
			{
				task->render();
			}
			return true;
		}
	}
}