#ifndef WATER_IMAGE_H
#define WATER_IMAGE_H
#include <string>
#include "file_base.h"
#include <memory>
#include "math3d/math3d.hpp"


namespace water
{
	namespace filesystem
	{
		enum class ImageDataFormat
		{
			DATA_UNKOWN,
			DATA_CHAR,
			DATA_FLOAT,
		};
		class Image: public FileBase
		{
		public:
			using FileBase::FileBase;
			~Image();
			virtual bool do_load();
			void get_data(unsigned char** data_ptr);
			void get_data(float** data_ptr);
			void set_data(int width, int height, int channels, unsigned char** data_ptr);
			ImageDataFormat get_data_format();
			math3d::Vector2 get_size();
			void release();
		public:
			int m_width{ 0 }, m_height{ 0 };
			int m_channel_in_file{ 0 };
		private:
			ImageDataFormat m_data_format{ ImageDataFormat::DATA_UNKOWN };
			unsigned char* m_data{ nullptr };
			float* m_data_f{ nullptr };
		};
		DECL_SHARED_PTR(Image);
	}
}

#endif // !WATER_IMAGE_H
