#include "window/window_win32.h"
#include "filesystem/filesystem.h"
#include <iostream>
#include "world/gameobjects/scene.h"

using namespace water;

void main() {
	IWindow* window = water::WindowWin32::Instance();
	window->set_window_size(1344, 750);
	window->on_init();
	window->set_window_title("Water");

	auto fs = filesystem::FileSystem::get_instance();
	fs->set_res_root("E:/Projects/C++/water/res");

	auto scn = world::Scene();
	scn.load_from_file("scenes/test.scene");

	while (!window->is_window_closed()) {
		window->on_frame();
		scn.tick(0);
	}
	window->on_destroy();
}