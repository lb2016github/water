#ifndef WATER_FILE_BASE_H
#define WATER_FILE_BASE_H
#include "common\common.h"
#include <string>
#include <memory>

namespace water {
	namespace filesystem {
		WaterInterface FileBase: public std::enable_shared_from_this<FileBase>
		{
		public:
			FileBase(const std::string& file_path) : m_file_path(file_path), m_loaded(false) {}
			FileBase(): m_loaded(false) {}
			virtual ~FileBase() {}
			void load() { do_load(); }
			void load(const std::string& file_path) {
				m_file_path = file_path;
				m_loaded = do_load();
			}
		protected:
			virtual bool do_load() = 0;
		public:
			// file_path is related path
			std::string m_file_path;
			bool m_loaded;
		};
	}
}

#endif // !WATER_FILE_BASE_H
