#ifndef WATER_WINDOW_H
#define WATER_WINDOW_H

#include "common/common.h"
#include <memory>
#include "math3d/math3d.hpp"
#include <string>
#include <memory>

namespace water {
	WaterInterface IWindowCallback
	{
		virtual void on_frame() = 0;
		virtual void on_key_callback(int key, int action) = 0;
	};


	WaterInterface IWindow : IPlugin
	{
		virtual bool is_full_screen() const = 0;
		virtual math3d::Vector2 get_window_size() const = 0;
		virtual void set_window_size(unsigned width, unsigned height) = 0;
		virtual std::string get_window_title() const = 0;
		virtual void set_window_title(std::string title) = 0;
		virtual bool is_window_closed() const = 0;
		virtual void add_callback(IWindowCallback* cb) = 0;
		virtual void remove_callback(IWindowCallback* cb) = 0;
		virtual int get_key_state(int key) = 0;
		virtual int get_mouse_state(int mouse_button) = 0;
		virtual math3d::Vector2 get_cursor_position() = 0;
		virtual void init_render_context() = 0;
		virtual void swap_frame_buffer() = 0;
	};

}

#endif
