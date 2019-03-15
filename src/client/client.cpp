#include "window/window_win32.h"

void main() {
	water::IWindow* window = water::WindowWin32::Instance();
	window->set_window_size(1344, 750);
	window->set_window_title("Water");
	window->on_init();
	while (!window->is_window_closed()) {
		window->on_frame();
	}
	window->on_destroy();
}