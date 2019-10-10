#ifndef WATER_TEXTURE_OPENGL_H
#define WATER_TEXTURE_OPENGL_H
#include "render/texture.h"
#include "glad/glad.h"
#include <map>

namespace water
{
	namespace render
	{

		struct TextureOpenGL: public Texture
		{
			TextureOpenGL(TextureType type, GLuint tex_obj = 0);
			~TextureOpenGL();
			virtual void bind(TextureUnit tex_unit);

			// init texture objects
			void init_texture_2d();

			GLuint m_texture_obj = { 0 };
			GLenum m_texture_target = { 0 };

		};


		class TextureManager
		{
		public:
			static TextureManager* get_instance();
			TextureOpenGL* get_texture(TextureDataPtr tex_ptr);

		private:
			std::map<TextureDataPtr, TextureOpenGL*> tex_map;


		};

	}
}


#endif // !WATER_TEXTURE_OPENGL_H
