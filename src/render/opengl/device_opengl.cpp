#include "render/opengl/device_opengl.h"
#include "render/opengl/render_program_opengl.h"
#include "render/opengl/render_state_manager_opengl.h"
#include "glad/glad.h"
#include "mesh_opengl.h"

namespace water
{
	namespace render
	{
		typedef Singleton<DeviceOpenGL> DeviceOpenGLSingleton;

		DeviceOpenGL::DeviceOpenGL()
		{
			m_program_manager_ptr = std::make_shared<ProgramManagerOpenGL>();
			m_render_state_manager_ptr = std::make_shared<RenderStateManagerOpenGL>();
		}
		DeviceOpenGL::~DeviceOpenGL()
		{
		}
		ProgramManagerPtr DeviceOpenGL::get_program_manager()
		{
			return m_program_manager_ptr;
		}
		RenderStateManagerPtr DeviceOpenGL::get_render_state_manager()
		{
			return m_render_state_manager_ptr;
		}
		void DeviceOpenGL::draw(DrawCommand draw_cmd, MeshDataPtr mesh_ptr)
		{
			auto mesh_proxy = MeshProxyManager::get_instance()->get_proxy(mesh_ptr);
			mesh_proxy->render(draw_cmd);
		}
		void DeviceOpenGL::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT| GL_STENCIL_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		}
	}
}