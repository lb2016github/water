#ifndef WATER_DEVICE_H
#define WATER_DEVICE_H
#include "render/render.h"
#include "mesh.h"
#include "draw_command.h"
#include "render/render_const.h"
#include "technique_common.h"
#include "render/render_target.h"
#include "render/texture.h"

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
			// creat render target
			virtual IRenderTargetPtr create_render_target(unsigned int width, unsigned int height) = 0;
			// draw
			virtual void draw(MeshDataPtr mesh_ptr) = 0;
			// clear screen
			virtual void clear() = 0;
			// create texture
			virtual TexturePtr create_texture(TextureType tex_type) = 0;
		};

		// devices
		enum DeviceType {
			DeviceTypeOpenGL,
		};

		DeviceBase* get_device();
		void set_device(DeviceType dy);

	}
}

#endif // !WATER_DEVICE_H
