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
			static IRenderTask* create_render_task(MeshPtr mesh, ProgramPtr program, RenderState render_state, ParameterMap param_map, IRenderTask* dependent);
		};


		class RenderTaskManager
		{
		public:
			void render();
			void add_task(IRenderTask* task);
			static RenderTaskManager* get_instance();
		protected:
			void before_render();
			void do_render();
			void end_render();
		private:
			RenderTaskManager();
			~RenderTaskManager();

		private:
			int cur_index;	// the index of current tasks
			RenderTaskList m_tasks[2];
			static RenderTaskManager* m_instance;
		};

	}
}

#endif // !WATER_RENDER_TASK_H
