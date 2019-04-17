#ifndef WATER_FILE_BASE_H
#define WATER_FILE_BASE_H
#include "common\common.h"
#include <string>

namespace water {
	namespace filesystem {
		WaterInterface FileBase {
		public:
			FileBase(const char* file_path) : m_file_path(file_path), m_loaded(false) { load(); }
			FileBase(): m_loaded(false) {}
			virtual ~FileBase() {}
			void load() { do_load(); }
			void load(const char* file_path) {
				m_file_path = file_path;
				m_loaded = do_load();
			}
		protected:
			virtual bool do_load() = 0;
		public:
			std::string m_file_path;
			bool m_loaded;
		};
	}
}

#endif // !WATER_FILE_BASE_H
