#ifndef WATER_RENDER_TASK_H
#define WATER_RENDER_TASK_H
#include "common/common.h"
#include <memory>
#include <vector>
#include <atomic>
#include "render/render.h"

namespace water
{
	namespace render
	{

		WaterInterface IRenderTask
		{
			virtual void render() = 0;
			virtual RenderTaskList get_depend_tasks() = 0;
			static RenderTaskPtr create_render_task(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map, RenderTaskPtr dependent);
		};


		struct RenderTaskBuffer
		{
			RenderTaskBuffer();
			// move constructor
			RenderTaskBuffer(RenderTaskBuffer&& buffer);
			// copy constructor
			RenderTaskBuffer(RenderTaskBuffer& buffer);
			// move assignment
			RenderTaskBuffer& operator= (RenderTaskBuffer&& buffer);
			// copy assignment 
			RenderTaskBuffer& operator= (const RenderTaskBuffer& buffer);
			// add task to buffer
			void add_task(RenderTaskPtr task);
			// clear buffer
			void clear();
			// set ready
			void set_ready(bool is_ready);
			// is ready
			bool is_ready() { return m_ready; }


			RenderTaskList m_tasks;	// data of tasks
			bool m_ready;	// is the buffer ready for rendering
		};

		/*
		RenderTread is used for do render task. The task data is from RenderTaskManager. 
		*/
		class RenderThread 
		{
		public:
			// constructor
			RenderThread();
			// do render
			void render();
		private:
			RenderTaskBuffer m_task_buffer; // the task buffer for rendering
		};

		/*
		RenderTaskManager supplies task buffers for render thread while render thread do the render task with suppled task buffer
		RenderTaskManager contains two basic buffers: the front buffer and the back buffer. Render thread copy the front buffer and render with it.
		Other game modules can add render task with function add_task. The added task is inn back buffer. When commit is called,
		the front buffer and back buffer will be swapped.
		*/
		class RenderTaskManager
		{
		public:
			// the real job is just swap front buffer and back buffer. The render thread will render the front buffer
			void commit();
			void add_task(RenderTaskPtr task);
			void get_front_buffer(RenderTaskBuffer& dst_buffer);
			static RenderTaskManager* get_instance();
		private:
			RenderTaskManager();
			~RenderTaskManager();

		private:
			RenderThread* m_render;	// render thread
			int m_front_buffer, m_back_buffer;
			RenderTaskBuffer m_task_buffers[2];	// buffers of render task
			static RenderTaskManager* m_instance;
		};

	}
}

#endif // !WATER_RENDER_TASK_H
