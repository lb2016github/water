#include "common/log.h"
#include "util.h"

namespace water {

#define LOG(msg, format) \
	int start_idx = std::strlen(msg);\
	va_list va;\
	va_start(va, format);\
	std::vsnprintf(msg + start_idx, MAX_LOG_LEN - start_idx, format, va);\
	va_end(va);\
	msg[MAX_LOG_LEN - 1] = '\0';\
	std::cout << msg << std::endl;	// todo 重定向输出


	void log_info(const char* format, ...) {
		char msg[MAX_LOG_LEN] = "[Info]: ";
		LOG(msg, format)
	}

	void log_warn(const char* format, ...) {
		char msg[MAX_LOG_LEN] = "[Warn]: ";
		LOG(msg, format)
	}

	void log_error(const char* format, ...) {
		char msg[MAX_LOG_LEN] = "[Error]: ";
		LOG(msg, format)
	}
	unsigned long create_id()
	{
		static unsigned long next_id = 0;
		return ++next_id;
	}
}
