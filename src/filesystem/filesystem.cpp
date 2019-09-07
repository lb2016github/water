#include "filesystem/filesystem.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <sstream>
#include "common/log.h"
#include <memory>

namespace water {
	namespace filesystem {

		FileSystem* instance = nullptr;

		bool FileSystem::is_file_exist(const char* file_path)
		{
			boost::filesystem::path path(file_path);
			return boost::filesystem::exists(path);
		}

		char * FileSystem::read_file(const char * file_path)
		{
			std::ifstream fs(file_path);
			if (!fs.is_open())
			{
				log_warn("Fail to read file %s", file_path);
				return nullptr;
			}
			fs.seekg(0, std::ios::end);
			int file_size = fs.tellg();
			char* buffer = (char*)malloc(file_size);
			fs.read(buffer, file_size);
			fs.close();
			return buffer;
		}

		int FileSystem::get_file_size(const char * file_path)
		{
			return boost::filesystem::file_size(file_path);
		}
		std::string FileSystem::get_absolute_path(const std::string related_path)
		{
			boost::filesystem::path related(related_path);
			auto path = boost::filesystem::absolute(related, m_res_path);
			return path.string();
		}
		void FileSystem::set_res_root(const std::string& res_path)
		{
			boost::filesystem::path path(res_path);
			if (!boost::filesystem::exists(path))
			{
				log_error("Res path is not exist: %s", res_path.c_str());
				return;
			}
			m_res_path = path;
		}
		FileSystem* FileSystem::get_instance()
		{
			if (instance == nullptr)
			{
				instance = new FileSystem();
			}
			return instance;
		}
	}

}
