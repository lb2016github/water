#include "window/window_win32.h"
#include "filesystem/filesystem.h"
#include <iostream>

void main() {
	water::filesystem::FileSystem fs;
	bool tmp = fs.is_file_exist("G:\\dts\\lb\\trunk\\res\\proj_config.xml");
	std::cout << "Exist" << tmp << std::endl;

	water::IWindow* window = water::WindowWin32::Instance();
	window->set_window_size(1344, 750);
	window->set_window_title("Water");
	window->on_init();
	while (!window->is_window_closed()) {
		window->on_frame();
	}
	window->on_destroy();
}