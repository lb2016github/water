#ifndef WATER_DEVICE_OPENGL_H
#define WATER_DEVICE_OPENGL_H

#include "render/device.h"
#include "common/singleton.hpp"

namespace water
{
	namespace render
	{
		class DeviceOpenGL : public DeviceBase
		{
		public:
			DeviceOpenGL();
			~DeviceOpenGL();
			// return the program manager pointer
			virtual ProgramManagerPtr get_program_manager();
			// return render state manager
			virtual RenderStateManagerPtr get_render_state_manager();
			// draw
			virtual void draw(DrawCommand draw_cmd, MeshDataPtr mesh_ptr);
			// clear screen
			virtual void clear();
			// creat render target
			virtual IRenderTargetPtr create_render_target(unsigned int width, unsigned int height);
			// create texture
			virtual TexturePtr create_texture(TextureType tex_type);
		protected:
			ProgramManagerPtr m_program_manager_ptr;
			RenderStateManagerPtr m_render_state_manager_ptr;
		};

	}
}


#endif // !WATER_DEVICE_OPENGL_H
