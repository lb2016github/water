#include "render_target_opengl.h"
#include "common/log.h"
#include "opengl_common.h"

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
		}
		RenderTargetOpengl::~RenderTargetOpengl()
		{
			glDeleteFramebuffers(1, &m_fbo);
			m_textures.clear();
		}
		bool RenderTargetOpengl::bind_for_writing()
		{
			if (m_fbo == 0) glGenFramebuffers(1, &m_fbo);
			if (m_attachment_dirty) update_attachments();
			GL_CHECK_ERROR
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
			GL_CHECK_ERROR
			glClear(GL_DEPTH_BUFFER_BIT);
			for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
			{
				auto rst = attachemnt_map.find(iter->first);
			}
			GL_CHECK_ERROR
			return true;
		}
		void RenderTargetOpengl::init_attachments(std::vector<Attachment> tex_attachments, std::vector<Attachment> render_buffer_attachments)
		{
			m_tex_attachments = tex_attachments;
			m_render_buffer_attachments = render_buffer_attachments;
			m_attachment_dirty = true;
			for each(auto attachment in m_tex_attachments)
			{
				auto rst = attachemnt_map.find(attachment);
				if (rst == attachemnt_map.end()) continue;
				auto gl_attach = rst->second;

				auto tex = std::make_shared<TextureOpenGL>(TEXTURE_2D);
				m_textures[attachment] = tex;
			}
		}

		TexturePtr RenderTargetOpengl::get_texture(Attachment attachement)
		{
			auto rst = m_textures.find(attachement);
			if (rst == m_textures.end())
			{
				return nullptr;
			}
			return rst->second;
		}
		void RenderTargetOpengl::reset()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			GL_CHECK_ERROR
		}
		void water::render::RenderTargetOpengl::update_attachments()
		{
			m_attachment_dirty = false;
			GL_CHECK_ERROR
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			std::vector<GLenum> draw_buffers;
			for each(auto attachment in m_tex_attachments)
			{
				auto rst = attachemnt_map.find(attachment);
				if (rst == attachemnt_map.end()) continue;
				auto gl_attach = rst->second;
				auto tex_ptr = std::dynamic_pointer_cast<TextureOpenGL>(get_texture(attachment));

				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				tex_ptr->m_texture_obj = tex;
				GLuint format = GL_RGBA;
				GLuint type = GL_UNSIGNED_BYTE;
				switch (gl_attach)
				{
				case GL_DEPTH_ATTACHMENT:
					format = GL_DEPTH_COMPONENT;
					type = GL_FLOAT;
					break;
				default:
					draw_buffers.push_back(gl_attach);
					break;
				}
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, type, nullptr);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glFramebufferTexture(GL_FRAMEBUFFER, gl_attach, tex, 0);
				GL_CHECK_ERROR
			}
			GL_CHECK_ERROR
			auto size = draw_buffers.size();
			if (size > 0)
			{
				glDrawBuffers(size, draw_buffers.data());
			}
			else
			{
				glDrawBuffer(GL_NONE);
			}

			GL_CHECK_ERROR
			for each(auto attachment in m_render_buffer_attachments)
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
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				log_info("Init framebuffer %d success", m_fbo);
			}
			else 
			{
				log_error("Init framebuffer %d failed", m_fbo);
			}
			GL_CHECK_ERROR
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			GL_CHECK_ERROR
		}
	}
}
