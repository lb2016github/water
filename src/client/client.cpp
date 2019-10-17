#include "window/window_win32.h"
#include "filesystem/filesystem.h"
#include <iostream>
#include "world/gameobjects/world.h"
#include "common/fps.h"
#include "render/render_thread.h"
#include <thread>

using namespace water;

struct WaterRenderThread: public FramePerSecond
{
	WaterRenderThread(IWindow* window) : m_window(window)
	{

	}
	void thread_run()
	{
		if (!m_inited)
		{
			m_window->init_render_context();
			m_inited = true;
		}
		while (true)
		{
			if (!m_render_thread.run())
			{
				continue;
			}
			m_window->swap_frame_buffer();
			FramePerSecond::on_frame();
			//std::cout << "render fps: " << m_fps << std::endl;
		}
	}
	void run()
	{
		if (!m_inited)
		{
			m_window->init_render_context();
			m_inited = true;
		}
		if (!m_render_thread.run())
		{
			return;
		}
		m_window->swap_frame_buffer();
		FramePerSecond::on_frame();
		//std::cout << "render fps: " << m_fps << std::endl;
	}
	render::RenderThread m_render_thread;
	IWindow* m_window;
	bool m_inited{ false };
};

void main() {
	WindowWin32* window = water::WindowWin32::Instance();
	window->set_window_size(1344, 750);
	window->on_init();
	window->set_window_title("Water");

	auto fs = filesystem::FileSystem::get_instance();
	fs->set_res_root("E:/Projects/C++/water/res");

	auto world = world::World::get_instance();
	world->set_window(window);
	auto scn = world->load_scene("scenes/test.scene");
	world->set_cur_scene(scn);
	window->add_callback(world);

	WaterRenderThread wrt(window);
	std::thread th(&WaterRenderThread::thread_run, wrt);
	if (th.joinable()) th.detach();

	while (!window->is_window_closed()) {
		window->on_frame();
		//wrt.run();
		//std::cout << "logic fps: " << window->m_fps << std::endl;
	}
	window->on_destroy();
}

