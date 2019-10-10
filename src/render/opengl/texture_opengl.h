#ifndef WATER_TEXTURE_OPENGL_H
#define WATER_TEXTURE_OPENGL_H
#include "render/texture.h"
#include "glad/glad.h"
#include <map>

namespace water
{
	namespace render
	{
		struct TextureOpenGL: Texture
		{
			TextureOpenGL(TextureDataPtr tex_ptr);
			~TextureOpenGL();
			virtual void bind(TextureUnit tex_unit);

			// init texture objects
			void init_texture_2d();

			TextureDataPtr m_tex_ptr = { nullptr };
			GLenum m_texture_obj;
			GLenum m_texture_target;

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
