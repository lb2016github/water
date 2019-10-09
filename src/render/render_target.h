#ifndef WATER_RENDER_TARGET_H
#define WATER_RENDER_TARGET_H
#include "common/common.h"
#include <vector>
#include "render/render_const.h"

namespace water
{
	namespace render
	{
		WaterInterface IRenderTarget
		{
			virtual bool bind_for_writing() = 0;
			virtual void init_attachments(std::vector<Attachment> tex_attachments, std::vector<Attachment> render_buffer_attachments) = 0;
		};
	}
}

#endif // !WATER_RENDER_TARGET_H
