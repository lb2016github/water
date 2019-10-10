#include "texture_opengl.h"
#include <assert.h>
#include "common/log.h"


namespace water
{
	namespace render
	{
		static TextureManager* instance = nullptr;

		TextureOpenGL::TextureOpenGL(TextureType tex_type, GLuint tex_obj): Texture(tex_type)
		{
			if (tex_obj >= 0)
			{
				m_texture_obj = tex_obj;
			}
			else
			{
				glGenTextures(1, &m_texture_obj);
			}
			switch (m_type)
			{
			case water::render::TEXTURE_2D:
				m_texture_target = GL_TEXTURE_2D;
				if (tex_obj < 0) init_texture_2d();
				break;
			default:
				break;
			}
		}
		TextureOpenGL::~TextureOpenGL()
		{
			if (m_texture_obj > 0)
			{
				glDeleteTextures(1, &m_texture_obj);
				m_texture_obj = -1;
			}

		}
		void TextureOpenGL::bind(TextureUnit tex_unit)
		{
			GLenum gl_unit = GL_TEXTURE0 + tex_unit - TEXTURE_UNIT_0;
			glActiveTexture(gl_unit);
			glBindTexture(m_texture_target, m_texture_obj);
		}
		void TextureOpenGL::init_texture_2d()
		{
			m_texture_target = GL_TEXTURE_2D;
			glBindTexture(GL_TEXTURE_2D, m_texture_obj);
			assert(m_data_ptr->images.size() > 0);
			auto img = m_data_ptr->images[0];
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
				auto ptr = new TextureOpenGL(tex_ptr->tex_type);
				ptr->set_tex_data(tex_ptr);
				tex_map[tex_ptr] = ptr;
			}
			return tex_map[tex_ptr];
		}
	}
}