#ifndef WATER_RENDER_THREAD_H
#define WATER_RENDER_THREAD_H

#include "render_task.h"

namespace water
{
	namespace render
	{
		/*
		RenderTread is used for do render task. The task data is from RenderTaskManager. 
		*/
		class RenderThread 
		{
		public:
			// constructor
			RenderThread();
			bool run();
		private:
			RenderTaskBuffer m_task_buffer; // the task buffer for rendering
		};

	}
}


#endif // !WATER_RENDER_THREAD_H
