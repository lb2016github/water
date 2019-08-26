#ifndef WATER_DEVICE_H
#define WATER_DEVICE_H
#include "render/render.h"
#include "mesh.h"
#include "draw_command.h"
#include "render/render_const.h"

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
			// draw
			virtual void draw(DrawCommand draw_cmd, MeshDataPtr mesh_ptr) = 0;
		};

		DeviceBase* get_device();

	}
}

#endif // !WATER_DEVICE_H
