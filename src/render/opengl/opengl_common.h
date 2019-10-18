#ifndef WATER_OPENGL_COMMON_H
#define WATER_OPENGL_COMMON_H
#include "common/log.h"


#ifdef WATER_DEBUG
#define GL_CHECK_ERROR \
{\
		GLenum e = glGetError();\
		if (e != 0){\
			log_error("GL Error %i in %s at line %i in %s", \
				e, __FUNCSIG__, __LINE__, __FILE__);\
		}\
		}
#else
#define GL_CHECK_ERROR

#endif // WATER_DEBUG



#endif // !WATER_OPENGL_COMMON_H
