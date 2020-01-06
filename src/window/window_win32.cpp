#include "window/window_win32.h"
#include "glad/glad.h"
#include "glfw3/glfw3.h"
#include "common/log.h"
#include <functional>

namespace water {

	static GLFWwindow* window;
	WindowWin32* m_instance = nullptr;

	//////////////////////////////////////// start callbacks ////////////////////////////////////////
	static void error_callback(int error, const char* desc) {
		char error_desc[128];
		sprintf(error_desc, "[GLFW Error]: %s", desc);
		log_error(error_desc);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (!m_instance)
		{
			return;
		}
		m_instance->on_key_callback(key, scancode, action, mods);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
	{
	}

	void cursor_position_callback(GLFWwindow* window, double x, double y)
	{

	}

	//////////////////////////////////////// end callbacks ////////////////////////////////////////

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

		// set key callback
		glfwSetKeyCallback(window, key_callback);
		
	}

	void WindowWin32::on_frame()
	{
		glfwGetFramebufferSize(window, &m_width, &m_height);
		for each(auto cb in m_callbacks)
		{
			cb->on_frame();
		}
		//glfwSwapBuffers(window);
		glfwPollEvents();
		FramePerSecond::on_frame();
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
		m_title = title;
		glfwSetWindowTitle(window, m_title.c_str());
	}

	void WindowWin32::add_callback(IWindowCallback* cb)
	{
		m_callbacks.insert(cb);
	}

	void WindowWin32::remove_callback(IWindowCallback* cb)
	{
		m_callbacks.erase(cb);
	}

	void WindowWin32::on_key_callback(int key, int scancode, int action, int mods)
	{
		for each(auto cb in m_callbacks)
		{
			cb->on_key_callback(key, action);
		}
	}

	int WindowWin32::get_key_state(int key)
	{
		return glfwGetKey(window, key);
	}

	int WindowWin32::get_mouse_state(int mouse_button)
	{
		return glfwGetMouseButton(window, mouse_button);
	}

	math3d::Vector2 WindowWin32::get_cursor_position()
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	void WindowWin32::init_render_context()
	{
		glfwMakeContextCurrent(window);
		// int glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			log_error("[GLAD]Failed to initialize glad");
			return;
		}
	}

	void WindowWin32::swap_frame_buffer()
	{
		glfwSwapBuffers(window);
	}

	WindowWin32* WindowWin32::Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new WindowWin32();
		}
		return m_instance;
	}

	WindowWin32::WindowWin32()
	{
	}


}