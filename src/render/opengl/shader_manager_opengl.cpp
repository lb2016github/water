#include "render/opengl/shader_manager_opengl.h"
#include "filesystem\filesystem.h"
#include "glad/glad.h"
#include "common/log.h"

namespace water
{
	namespace render
	{
		unsigned int ShaderManagerOpenGL::load(ShaderType & shader_type, const char * file_path)
		{
			ShaderMap::iterator rst = m_shader_map.find(file_path);
			if (rst != m_shader_map.end())
			{
				return rst->second;
			}

			char* buffer = filesystem::FileSystem::instance.read_file(file_path);
			if (!buffer) {
				return;
			}
			GLuint shader = glCreateShader(get_shader_type(shader_type));
			glShaderSource(shader, 1, &buffer, NULL); 
			glCompileShader(shader);
			// check is compile succeed
			GLint result = GL_FALSE;
			GLint log_length = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
			if (log_length > 0)
			{
				char* msg = new char[log_length];
				glGetShaderInfoLog(shader, log_length, NULL, msg);
				log_info(msg);
				delete[] msg;
			}
			if (!result)
			{
				log_warn("Compile Shader(%s) failed", file_path);
			}
			else
			{
				m_shader_map[file_path] = shader;
			}
		}

		GLuint get_shader_type(ShaderType& shader_type)
		{
			switch (shader_type)
			{
			case VertexShader:
				return GL_VERTEX_SHADER;
			case FragmentShader:
				return GL_FRAGMENT_SHADER;
			case GeometryShader:
				return GL_FRAGMENT_SHADER;
			default:
				break;
			return 0;
			}
		}
	}
}
