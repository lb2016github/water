#include "window/window_win32.h"
#include "filesystem/filesystem.h"
#include <iostream>
#include "world/gameobjects/world.h"

using namespace water;

void main() {
	IWindow* window = water::WindowWin32::Instance();
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

	while (!window->is_window_closed()) {
		window->on_frame();
	}
	window->on_destroy();
}
