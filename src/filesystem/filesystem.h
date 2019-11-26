#ifndef WATER_FILESYSTEM_H
#define WATER_FILESYSTEM_H
#include "common/common.h"
#include "boost/filesystem.hpp"

namespace water {
	namespace filesystem {
		typedef boost::filesystem::path Path;

		class FileSystem {
		public:
			bool is_file_exist(const char* file_path);
			char* read_file(const char* file_path);
			int get_file_size(const char* file_path);
			std::string get_absolute_path(const std::string related_path);
			void set_res_root(const std::string& res_path);
			std::string get_extension(const std::string& filepath);

			static FileSystem* get_instance();

		private:
			FileSystem() {}

		public:
			boost::filesystem::path m_res_path;
		};

	}
}

#endif

