#ifndef WATER_COMMON_H
#define WATER_COMMON_H

#define WaterInterface struct

namespace water {

	WaterInterface IPlugin{
		virtual void on_init() = 0;
		virtual void on_frame() = 0;
		virtual void on_destroy() = 0;
	};
}

#endif