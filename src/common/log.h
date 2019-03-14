#ifndef WATER_LOG_H
#define WATER_LOG_H
#include <iostream>

namespace water {
	void _log(const char* msg) {
		std::cout << msg;
	}

	void log_info(const char* msg) {
		std::string new_msg = "[Info]: " + std::string(msg) + "\n";
		_log(new_msg.c_str());
	}

	void log_warn(const char* msg) {
		std::string new_msg = "[Warn]: " + std::string(msg) + "\n";
		_log(new_msg.c_str());
	}

	void log_error(const char* msg) {
		std::string new_msg = "[Error]: " + std::string(msg) + "\n";
		_log(new_msg.c_str());
	}
}

#endif
