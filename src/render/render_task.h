#ifndef WATER_RENDER_TASK_H
#define WATER_RENDER_TASK_H
#include "common/common.h"
#include <memory>
#include <vector>
#include "render/render.h"

namespace water
{
	namespace render
	{

		WaterInterface IRenderTask
		{
			virtual void render() = 0;
			virtual RenderTaskList get_depend_tasks() = 0;
			static IRenderTask* create_render_task(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map, IRenderTask* dependent);
		};


		class RenderTaskManager
		{
		public:
			// the real job is just swap front buffer and back buffer. The render thread will render the front buffer
			void render();
			void add_task(IRenderTask* task);
			static RenderTaskManager* get_instance();
		protected:
			void before_render();
			void do_render();
			void end_render();
			void inline swap_buffer(int& a, int&b);
		private:
			RenderTaskManager();
			~RenderTaskManager();

		private:
			int m_front_buffer, m_back_buffer, m_render_buffer;
			RenderTaskBuffer m_task_buffers[3];	// buffers of render task
			static RenderTaskManager* m_instance;
		};

		class RenderTaskBuffer
		{
		public:
			// add task to buffer
			void add_task(IRenderTask* task);
			// clear buffer
			void clear();
			// set ready
			void set_ready(bool is_ready);
		private:
			RenderTaskList m_tasks;	// data of tasks
			bool m_ready;	// is the buffer ready for rendering
		};

		class RenderThread 
		{

		};
	}
}

#endif // !WATER_RENDER_TASK_H
