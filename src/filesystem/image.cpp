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
			auto fs = FileSystem::get_instance();
			auto abs_path = fs->get_absolute_path(m_file_path);
			auto extension = fs->get_extension(m_file_path);
			void* data_ptr = nullptr;
			if (extension == ".hdr")
			{
				m_data_f = stbi_loadf(abs_path.c_str(), &m_width, &m_height, &m_channel_in_file, 4);
				m_data_format = ImageDataFormat::DATA_FLOAT;
				data_ptr = m_data_f;
			}
			else
			{
				m_data = stbi_load(abs_path.c_str(), &m_width, &m_height, &m_channel_in_file, 4);
				m_data_format = ImageDataFormat::DATA_CHAR;
				data_ptr = m_data;
			}
			if (data_ptr == nullptr)
			{
				log_error("[Image]Failed to load image: %s", m_file_path.c_str());
				return false;
			}
			log_info("[Image]Success to load image: %s", m_file_path.c_str());
			return true;
		}
		void Image::get_data(unsigned char ** data_ptr)
		{
			*data_ptr = m_data;
		}
		void Image::get_data(float ** data_ptr)
		{
			*data_ptr = m_data_f;
		}
		void Image::set_data(int width, int height, int channels, unsigned char ** data_ptr)
		{
			m_width = width;
			m_height = height;
			m_channel_in_file = channels;
			m_data = *data_ptr;
			m_loaded = true;
			m_data_format = ImageDataFormat::DATA_CHAR;
		}
		ImageDataFormat Image::get_data_format()
		{
			return m_data_format;
		}
		math3d::Vector2 Image::get_size()
		{
			return math3d::Vector2(m_width, m_height);
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