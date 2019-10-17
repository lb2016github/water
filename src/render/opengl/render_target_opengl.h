#ifndef WATER_RENDER_TARGET_OPENGL_H
#define WATER_RENDER_TARGET_OPENGL_H
#include "glad/glad.h"
#include <map>
#include <vector>
#include "render/render_const.h"
#include "common/common.h"
#include "render/render_target.h"
#include "render/opengl/texture_opengl.h"

namespace water
{
	namespace render
	{
		class RenderTargetOpengl: public IRenderTarget
		{
		public:
			RenderTargetOpengl(unsigned int width, unsigned int height);
			~RenderTargetOpengl();
			virtual bool bind_for_writing();
			virtual void init_attachments(std::vector<Attachment> tex_attachments, std::vector<Attachment> render_buffer_attachments);
			virtual TexturePtr get_texture(Attachment attachement);
			virtual void reset();
		private:
			void update_attachments();
		private:
			GLuint m_fbo{ 0 };
			std::map<Attachment, TexturePtr> m_textures;
			unsigned int m_width, m_height;
			std::vector<Attachment> m_tex_attachments, m_render_buffer_attachments;
			bool m_attachment_dirty{ false };
		};

	}
}

#endif // !WATER_RENDER_TARGET_OPENGL_H
