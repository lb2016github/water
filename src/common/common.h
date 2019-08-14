#ifndef WATER_COMMON_H
#define WATER_COMMON_H

#define WaterInterface struct

namespace water {

	WaterInterface IPlugin{
		virtual void on_init() = 0;
		virtual void on_frame() = 0;
		virtual void on_destroy() = 0;
	};

#define SAFE_DELETE(ptr) if(ptr != nullptr) delete ptr;
#define SAFE_DELETE_ARRAY(ptr) if (ptr != nullptr) delete[] ptr;
}

#endif