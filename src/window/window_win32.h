#ifndef WATER_WINDOW_WIN32_H
#define WATER_WINDOW_WIN32_H

#include "window/window_interface.h"
#include "math3d\math3d.hpp"
#include <memory>
#include <string>

namespace water {
	class WindowWin32 : public IWindow {
	public:
		void on_init();
		void on_frame();
		void on_destroy();

		virtual bool is_full_screen() const;
		virtual bool is_window_closed() const;
		virtual math3d::Vector2 get_window_size() const;
		virtual void set_window_size(unsigned width, unsigned height);
		virtual std::string get_window_title() const;
		virtual void set_window_title(std::string title);

		static WindowWin32* Instance();

	private:
		WindowWin32();

	protected:
		unsigned m_width;
		unsigned m_height;
		std::string m_title;
	private:
		static WindowWin32 m_instance;
	};
}


#endif
