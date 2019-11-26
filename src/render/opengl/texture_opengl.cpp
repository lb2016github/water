#include "texture_opengl.h"
#include <assert.h>
#include "common/log.h"
#include "opengl_common.h"


namespace water
{
	namespace render
	{
		void commit_image_data(GLuint target, filesystem::ImagePtr img)
		{
			switch (img->get_data_format())
			{
			case filesystem::ImageDataFormat::DATA_CHAR:
				unsigned char* img_data;
				img->get_data(&img_data);
				glTexImage2D(target, 0, GL_RGBA, img->m_width, img->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
				break;
			case filesystem::ImageDataFormat::DATA_FLOAT:
				float* img_data_f;
				img->get_data(&img_data_f);
				glTexImage2D(target, 0, GL_RGBA16F, img->m_width, img->m_height, 0, GL_RGBA, GL_FLOAT, img_data_f);
				break;
			default:
				break;
			}

		}
		TextureOpenGL::TextureOpenGL(TextureType tex_type, GLuint tex_obj): Texture(tex_type)
		{
			if (tex_obj > 0)
			{
				m_texture_obj = tex_obj;
			}
			switch (m_type)
			{
			case TEXTURE_2D:
				m_texture_target = GL_TEXTURE_2D;
				break;
			case TEXTURE_CUBE:
				m_texture_target = GL_TEXTURE_CUBE_MAP;
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
			if (m_texture_obj <= 0)
			{
				glGenTextures(1, &m_texture_obj);
			}
			if (m_data_dirty)
			{
				switch (m_type)
				{
				case TEXTURE_2D:
					init_texture_2d();
					break;
				case TEXTURE_CUBE:
					init_texture_cube();
					break;
				default:
					break;
				}
				m_data_dirty = false;
			}
			GLenum gl_unit = GL_TEXTURE0 + tex_unit - TEXTURE_UNIT_0;
			glActiveTexture(gl_unit);
			glBindTexture(m_texture_target, m_texture_obj);
		}
		void TextureOpenGL::set_tex_data(TextureDataPtr ptr)
		{
			Texture::set_tex_data(ptr);
			m_data_dirty = true;
		}
		void TextureOpenGL::init_texture_2d()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture_obj);
			if(m_data_ptr->images.size() > 0)
			{
				auto img = m_data_ptr->images[0];
				commit_image_data(GL_TEXTURE_2D, img);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
		void TextureOpenGL::init_texture_cube()
		{
			assert(m_data_ptr->images.size() >= 6);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_obj);
			GL_CHECK_ERROR
			GLuint tex_types[] =
			{
				GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			};
			GL_CHECK_ERROR
			for (int i = 0; i < 6; ++i)
			{
				auto img = m_data_ptr->images[i];
				auto tag = tex_types[i];
				commit_image_data(tex_types[i], img);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			}
			GL_CHECK_ERROR
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			GL_CHECK_ERROR
		}
	}
}