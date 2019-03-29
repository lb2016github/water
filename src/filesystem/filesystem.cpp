#include "filesystem/filesystem.h"
#include "boost/filesystem.hpp"

namespace water {
	namespace filesystem {

		bool FileSystem::is_file_exist(const char* file_path)
		{
			boost::filesystem::path path(file_path);
			return boost::filesystem::exists(path);
		}

	}

}
