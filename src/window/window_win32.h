#ifndef WATER_WINDOW_WIN32_H
#define WATER_WINDOW_WIN32_H

#include "window/window_interface.h"
#include <memory>
#include <string>

namespace water {
	class WindowWin32 : public IWindow {
	public:
		void on_init();
		void on_frame();
		void on_destroy();

		virtual bool is_full_screen();

		static WindowWin32* Instance();

	private:
		WindowWin32() {}

	private:
		unsigned m_width;
		unsigned m_height;
		std::string m_title;
		static WindowWin32 m_instance;
	};
}


#endif
