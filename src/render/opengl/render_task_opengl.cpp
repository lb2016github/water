#include "render_task_opengl.h"
#include "render/material.h"


namespace water
{
	namespace render
	{
		RenderTaskOpenGL::RenderTaskOpenGL(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map):
			mesh_ptr(mesh), program_ptr(program), render_state(render_state), param_map(param_map)
		{
		}
		RenderTaskOpenGL::~RenderTaskOpenGL()
		{
		}
		void RenderTaskOpenGL::render()
		{

		}
		RenderTaskList RenderTaskOpenGL::get_depend_tasks()
		{
			return RenderTaskList();
		}
		RenderTaskPtr RenderTaskOpenGL::create_render_task(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map)
		{
			RenderTaskOpenGL* ogl = new RenderTaskOpenGL(mesh, program, render_state, param_map);
			std::shared_ptr<RenderTaskOpenGL> ptr(ogl);
			return ptr;
		}
	}
}
