#ifndef WATER_LOG_H
#define WATER_LOG_H
#include <iostream>
#include <stdarg.h>

#define MAX_LOG_LEN 512

namespace water {
	void log_info(const char* format, ...);
	void log_warn(const char* format, ...);
	void log_error(const char* format, ...);

}

#endif
