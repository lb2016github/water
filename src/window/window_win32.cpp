#include "window/window_win32.h"
#include "glfw3/include/glfw3.h"
#include "common/log.h"

namespace water {

	static GLFWwindow* window;

	void WindowWin32::on_init()
	{
		if (window)
		{
			return;
		}
		if (!glfwInit()) {
			log_error("Init glfw failed");
			return;
		}

		window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (!window)
		{
			log_error("Create glfw window failed");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		
	}

	void WindowWin32::on_frame()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void WindowWin32::on_destroy()
	{
		glfwTerminate();
	}

	bool WindowWin32::is_full_screen()
	{
		// todo
		return true;
	}

	water::WindowWin32* WindowWin32::Instance()
	{
		return &m_instance;
	}

}