#ifndef WATER_DEVICE_H
#define WATER_DEVICE_H
#include "render/render.h"

namespace water
{
	namespace render
	{
		WaterInterface DeviceBase
		{
			// return the program manager pointer
			virtual ProgramManagerPtr get_program_manager() = 0;
			// return render state manager
			virtual RenderStateManagerPtr get_render_state_manager() = 0;
		};

		DeviceBase* get_device();

	}
}

#endif // !WATER_DEVICE_H
