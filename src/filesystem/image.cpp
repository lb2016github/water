#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "common/log.h"
#include "filesystem.h"

namespace water
{
	namespace filesystem
	{
		bool Image::do_load()
		{
			stbi_set_flip_vertically_on_load(true);
			auto abs_path = FileSystem::get_instance()->get_absolute_path(m_file_path);
			m_data = stbi_load(abs_path.c_str(), &m_width, &m_height, &m_channel_in_file, 4);
			if (m_data == nullptr)
			{
				log_error("[Image]Failed to load image: %s", m_file_path.c_str());
				return false;
			}
			log_info("[Image]Success to load image: %s", m_file_path.c_str());
			return true;
		}
		unsigned char* Image::get_data()
		{
			return m_data;
		}
		void Image::release()
		{
			if (m_data)
			{
				stbi_image_free(m_data);
				m_data = nullptr;
			}
		}
		Image::~Image()
		{
			release();
		}
	}
}