#ifndef WATER_SHADER_MANAGER_OPENGL_H
#define WATER_SHADER_MANAGER_OPENGL_H
#include "common\common.h"
#include "render/i_device.h"
#include <map>
#include <string>

namespace water {
	namespace render {

		typedef std::map<std::string, unsigned int> ShaderMap;

		class ShaderManagerOpenGL: public IShaderManager {
		public:
			virtual unsigned int load(ShaderType& shader_type, const char* file_path);
		private:
			ShaderMap m_shader_map;
		};
	}
}

#endif // !WATER_SHADER_MANAGER_H
