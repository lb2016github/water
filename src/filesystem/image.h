#ifndef WATER_IMAGE_H
#define WATER_IMAGE_H
#include <string>
#include "file_base.h"
#include <memory>


namespace water
{
	namespace filesystem
	{
		class Image: public FileBase
		{
		public:
			using FileBase::FileBase;
			~Image();
			virtual bool do_load();
			unsigned char* get_data();
			void release();
		public:
			int m_width = { 0 }, m_height = { 0 };
			int m_channel_in_file = { 0 };
		private:
			unsigned char* m_data = { nullptr };

		};
		DECL_SHARED_PTR(Image);
	}
}

#endif // !WATER_IMAGE_H
