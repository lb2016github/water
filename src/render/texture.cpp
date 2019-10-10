#include "texture.h"

namespace water
{
	namespace render
	{
		void TextureData::load()
		{
			for each (auto img in images)
			{
				if (!img->m_loaded)
				{
					img->load();
				}
			}
		}
		Texture::Texture(TextureType tex_type): m_type(tex_type)
		{
		}
		Texture::~Texture()
		{
			m_data_ptr = nullptr;
		}
		void Texture::set_tex_data(TextureDataPtr ptr)
		{
			m_data_ptr = ptr;
		}
	}
}