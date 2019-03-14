#ifndef WATER_COMMON_H
#define WATER_COMMON_H

#define Interface struct

namespace water {

	Interface IPlugin{
		virtual void on_init() = 0;
		virtual void on_frame() = 0;
		virtual void on_destroy() = 0;
	};
}

#endif