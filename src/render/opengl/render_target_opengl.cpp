#include "render_target_opengl.h"

namespace water
{
	namespace render
	{
		static std::map<Attachment, GLuint> attachemnt_map = {
			{ATTACHMENT_DEPTH, GL_DEPTH_ATTACHMENT},
			{ATTACHMENT_STENCIL, GL_STENCIL_ATTACHMENT},
			{ATTACHMENT_DEPTH_STENCIL, GL_DEPTH_STENCIL_ATTACHMENT},
			{ATTACHMENT_COLOR_0,GL_COLOR_ATTACHMENT0},
			{ATTACHMENT_COLOR_1,GL_COLOR_ATTACHMENT1},
			{ATTACHMENT_COLOR_2,GL_COLOR_ATTACHMENT2},
			{ATTACHMENT_COLOR_3,GL_COLOR_ATTACHMENT3},
			{ATTACHMENT_COLOR_4,GL_COLOR_ATTACHMENT4},
		};

		RenderTargetOpengl::RenderTargetOpengl(unsigned int width, unsigned int height):
			m_width(width), m_height(height)
		{
			glGenFramebuffers(1, &m_fbo);
		}
		RenderTargetOpengl::~RenderTargetOpengl()
		{
			glDeleteFramebuffers(1, &m_fbo);
			for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
			{
				glDeleteTextures(1, &(iter->second));
			}
			m_textures.clear();
		}
		bool RenderTargetOpengl::bind_for_writing()
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
			return true;
		}
		void RenderTargetOpengl::init_attachments(std::vector<Attachment> tex_attachments, std::vector<Attachment> render_buffer_attachments)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			for each(auto attachment in tex_attachments)
			{
				auto rst = attachemnt_map.find(attachment);
				if (rst == attachemnt_map.end()) continue;
				auto gl_attach = rst->second;

				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				GLuint format = GL_RGBA;
				switch (gl_attach)
				{
				case GL_DEPTH_ATTACHMENT:
					format = GL_DEPTH_COMPONENT;
					break;
				default:
					break;
				}
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, nullptr);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINE);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINE);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glFramebufferTexture(GL_FRAMEBUFFER, gl_attach, tex, 0);

				m_textures[attachment] = tex;
			}

			for each(auto attachment in render_buffer_attachments)
			{
				auto rst = attachemnt_map.find(attachment);
				if (rst == attachemnt_map.end()) return;
				auto gl_attach = rst->second;

				GLuint render_buffer;
				glGenRenderbuffers(1, &render_buffer);
				glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
				switch (gl_attach)
				{
				case GL_DEPTH_STENCIL_ATTACHMENT:
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
					break;
				case GL_DEPTH_ATTACHMENT:
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
					break;
				default:
					break;
				}
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, gl_attach, GL_RENDERBUFFER, render_buffer);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
