#include "texture_opengl.h"
#include <assert.h>
#include "common/log.h"


namespace water
{
	namespace render
	{
		static TextureManager* instance = nullptr;

		TextureOpenGL::TextureOpenGL(TextureDataPtr tex_ptr): m_tex_ptr(tex_ptr)
		{
			glGenTextures(1, &m_texture_obj);
			tex_ptr->load();
			switch (tex_ptr->tex_type)
			{
			case TEXTURE_2D:
				init_texture_2d();
				break;
			default:
				log_error("[TextureOpenGL]Unkown texture type: %i", tex_ptr->tex_type);
				break;
			}
		}
		TextureOpenGL::~TextureOpenGL()
		{
			m_tex_ptr = nullptr;
			if (m_texture_obj > 0)
			{
				glDeleteTextures(1, &m_texture_obj);
				m_texture_obj = -1;
			}

		}
		void TextureOpenGL::bind(GLenum tex_unit)
		{
			glActiveTexture(tex_unit);
			glBindTexture(m_texture_target, m_texture_obj);
		}
		void TextureOpenGL::init_texture_2d()
		{
			m_texture_target = GL_TEXTURE_2D;
			glBindTexture(GL_TEXTURE_2D, m_texture_obj);
			assert(m_tex_ptr->images.size() > 0);
			auto img = m_tex_ptr->images[0];
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->m_width, img->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->get_data());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		TextureManager* TextureManager::get_instance()
		{
			if (instance == nullptr)
			{
				instance = new TextureManager();
			}
			return instance;
		}
		TextureOpenGL* TextureManager::get_texture(TextureDataPtr tex_ptr)
		{
			auto rst = tex_map.find(tex_ptr);
			if (rst == tex_map.end())
			{
				tex_map[tex_ptr] = new TextureOpenGL(tex_ptr);
			}
			return tex_map[tex_ptr];
		}
	}
}