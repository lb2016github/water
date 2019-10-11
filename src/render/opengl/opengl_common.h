#ifndef WATER_OPENGL_COMMON_H
#define WATER_OPENGL_COMMON_H
#include "common/log.h"

#define GL_CHECK_ERROR {\
		GLenum e = glGetError();\
		if (e != 0){\
			log_error("GL Error %i in %s at line %i in %s", \
				e, __FUNCSIG__, __LINE__, __FILE__);\
		}\
		}

#endif // !WATER_OPENGL_COMMON_H
