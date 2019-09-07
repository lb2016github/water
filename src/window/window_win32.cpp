#include "window/window_win32.h"
#include "glad/glad.h"
#include "glfw3/glfw3.h"
#include "common/log.h"

namespace water {

	static GLFWwindow* window;

	static void error_callback(int error, const char* desc) {
		char error_desc[128];
		sprintf(error_desc, "[GLFW Error]: %s", desc);
		log_error(error_desc);
	}

	void WindowWin32::on_init()
	{
		if (window)
		{
			return;
		}

		glfwSetErrorCallback(error_callback);

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
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void WindowWin32::on_destroy()
	{
		glfwTerminate();
	}

	bool WindowWin32::is_full_screen() const
	{
		//todo 
		return false;
	}

	bool WindowWin32::is_window_closed() const
	{
		return glfwWindowShouldClose(window);
	}

	math3d::Vector2 WindowWin32::get_window_size() const
	{
		return math3d::Vector2(m_width, m_height);
	}

	void WindowWin32::set_window_size(unsigned width, unsigned height)
	{
		m_width = width;
		m_height = height;
		if (window)
		{
			glfwSetWindowSize(window, m_width, m_height);
		}
	}

	std::string WindowWin32::get_window_title() const
	{
		return m_title;
	}

	void WindowWin32::set_window_title(std::string title)
	{
		glfwSetWindowTitle(window, m_title.c_str());
	}

	water::WindowWin32* WindowWin32::Instance()
	{
		return &m_instance;
	}

	WindowWin32::WindowWin32()
	{
	}

	WindowWin32 WindowWin32::m_instance;

}