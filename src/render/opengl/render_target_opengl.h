#ifndef WATER_RENDER_TARGET_OPENGL_H
#define WATER_RENDER_TARGET_OPENGL_H
#include "glad/glad.h"
#include <map>
#include <vector>
#include "render/render_const.h"
#include "common/common.h"
#include "render/render_target.h"

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
			GLuint m_fbo;;
			std::map<Attachment, GLuint> m_textures;
			unsigned int m_width, m_height;
		};

	}
}

#endif // !WATER_RENDER_TARGET_OPENGL_H
