#ifndef WATER_RENDER_TARGET_H
#define WATER_RENDER_TARGET_H
#include "common/common.h"
#include <vector>
#include "render/render_const.h"
#include <memory>
#include "texture.h"

namespace water
{
	namespace render
	{
		WaterInterface IRenderTarget: std::enable_shared_from_this<IRenderTarget>
		{
			virtual bool bind_for_writing() = 0;
			virtual void init_attachments(std::vector<Attachment> tex_attachments, std::vector<Attachment> render_buffer_attachments) = 0;
			virtual TexturePtr get_texture(Attachment attachement) = 0;
			virtual void reset() = 0;
		};

		DECL_SHARED_PTR(IRenderTarget);
	}
}

#endif // !WATER_RENDER_TARGET_H
