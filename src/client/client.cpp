#include "window/window_win32.h"

void main() {
	water::IWindow* window = water::WindowWin32::Instance();
	window->on_init();
	while (true) {
		window->on_frame();
	}
}