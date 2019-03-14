#ifndef WATER_WINDOW_H
#define WATER_WINDOW_H

#include "common/common.h"
#include <memory>

namespace water {
	Interface IWindow : IPlugin{
		virtual bool is_full_screen() = 0;
	};
}

#endif
