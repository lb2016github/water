#ifndef WATER_RENDER_TASK_H
#define WATER_RENDER_TASK_H
#include "common/common.h"
#include <memory>
#include <vector>
#include <atomic>
#include "render/render.h"
#include "render/material.h"
#include "mesh.h"
#include "draw_command.h"
#include "render_target.h"

namespace water
{
	namespace render
	{
		WaterInterface IRenderTask: public std::enable_shared_from_this<IRenderTask>
		{
			virtual void render() = 0;
			virtual RenderTaskList get_depend_tasks() = 0;
		};

		struct RenderTask: public IRenderTask
		{
			RenderTask(MeshDataPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map, RenderTaskPtr dependent);
			virtual ~RenderTask();

			virtual void render();
			virtual RenderTaskList get_depend_tasks();

			MeshDataPtr mesh_ptr;				// mesh data
			ProgramPtr program_ptr;			// program pointer
			RenderStateInfo render_state;	// render state
			ParameterMap param_map;	// parameter map
		};

		struct RenderTargetTask : public IRenderTask
		{
			enum Command
			{
				CMD_BIND_FOR_WIRTE,
				CMD_RESET,
			};
			RenderTargetTask(Command cmd, IRenderTargetPtr ptr);
			virtual void render();
			virtual RenderTaskList get_depend_tasks();

			IRenderTargetPtr m_rtpr;
			Command m_cmd;
		};


		struct RenderTaskBuffer
		{
			RenderTaskBuffer();
			// move constructor
			RenderTaskBuffer(RenderTaskBuffer&& buffer);
			// copy constructor
			RenderTaskBuffer(const RenderTaskBuffer& buffer);
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
			bool is_front_ready();
			void tick();
			static RenderTaskManager* get_instance();
		private:
			RenderTaskManager();
			~RenderTaskManager();

		private:
			int m_front_buffer = { 0 }, m_back_buffer = { 1 };
			RenderTaskBuffer m_task_buffers[2];	// buffers of render task
			static RenderTaskManager* m_instance;
		};

	}
}

#endif // !WATER_RENDER_TASK_H
