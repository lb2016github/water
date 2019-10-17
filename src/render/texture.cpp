#include "texture.h"
#include "device.h"

namespace water
{
	namespace render
	{
		static TextureManager* instance = nullptr;
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
		TextureManager* TextureManager::get_instance()
		{
			if (instance == nullptr)
			{
				instance = new TextureManager();
			}
			return instance;
		}
		TexturePtr TextureManager::get_texture(TextureDataPtr tex_ptr)
		{
			auto rst = tex_map.find(tex_ptr);
			if (rst == tex_map.end())
			{
				auto device = get_device();
				auto ptr = device->create_texture(tex_ptr->tex_type);
				ptr->set_tex_data(tex_ptr);
				tex_map[tex_ptr] = ptr;
			}
			return tex_map[tex_ptr];
		}
	}
}