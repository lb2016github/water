#ifndef RENDER_TASK_OPENGL_H
#define RENDER_TASK_OPENGL_H

#include "render/render_task.h"
#include "render/material.h"

namespace water
{
	namespace render
	{
		class RenderTaskOpenGL : public IRenderTask
		{
		public:
			RenderTaskOpenGL(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map);
			~RenderTaskOpenGL();
			virtual void render();
			virtual RenderTaskList get_depend_tasks();
			static RenderTaskPtr create_render_task(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map);
		private:
			MeshPtr mesh_ptr;				// mesh data
			ProgramPtr program_ptr;			// program pointer
			RenderStateInfo render_state;	// render state
			ParameterMap param_map;	// parameter map
		};
	}
}

#endif // !RENDER_TASK_OPENGL_H
