#include "render_task_opengl.h"
#include "render/material.h"
#include "render/render_program.h"
#include "render/render_object.h"


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
			// use program and apply parameters
			program_ptr->use_program();
			program_ptr->apply_parameters(param_map);
			// draw meshes
			mesh_ptr->render();
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
