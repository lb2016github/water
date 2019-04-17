#ifndef WATER_FILESYSTEM_H
#define WATER_FILESYSTEM_H
#include "common/common.h"

namespace water {
	namespace filesystem {
		class FileSystem {
		public:
			bool is_file_exist(const char* file_path);
			char* read_file(const char* file_path);
			int get_file_size(const char* file_path);
		};



	}
}

#endif

