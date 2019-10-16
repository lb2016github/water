#ifndef WATER_WINDOW_WIN32_H
#define WATER_WINDOW_WIN32_H

#include "window/window_interface.h"
#include "math3d\math3d.hpp"
#include <memory>
#include <string>
#include <set>

namespace water {
	class WindowWin32 : public IWindow {
	public:
		void on_init();
		void on_frame();
		void on_destroy();

		virtual void* get_context();
		virtual void make_current(bool is_current);
		virtual bool is_full_screen() const;
		virtual bool is_window_closed() const;
		virtual math3d::Vector2 get_window_size() const;
		virtual void set_window_size(unsigned width, unsigned height);
		virtual std::string get_window_title() const;
		virtual void set_window_title(std::string title);
		virtual void add_callback(IWindowCallback* cb);
		virtual void remove_callback(IWindowCallback* cb);
		virtual int get_key_state(int key);
		virtual int get_mouse_state(int mouse_button);
		virtual math3d::Vector2 get_cursor_position();
	public:
		void on_key_callback(int key, int scancode, int action, int mods);

		static WindowWin32* Instance();

	private:
		WindowWin32();

	protected:
		int m_width = { 1344 };
		int m_height = { 750 };
		std::string m_title = { "Window" };
		std::set<IWindowCallback*> m_callbacks;
	};
}


#endif
