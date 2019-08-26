#include "render/opengl/device_opengl.h"
#include "render/opengl/render_program_opengl.h"
#include "render/opengl/render_state_manager_opengl.h"

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
	}
}