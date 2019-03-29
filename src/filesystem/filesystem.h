#ifndef WATER_FILESYSTEM_H
#define WATER_FILESYSTEM_H
#include "common/common.h"

namespace water {
	namespace filesystem {
		class FileSystem {
		public:
			bool is_file_exist(const char* file_path);
		};



	}
}

#endif

