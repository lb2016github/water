#include "render/opengl/render_program_opengl.h"
#include "filesystem\filesystem.h"
#include "glad/glad.h"
#include "common/log.h"
#include "render/material.h"
#include "render/device.h"
#include <sstream>
#include "texture_opengl.h"
#include "render/light.h"
#include "opengl_common.h"

namespace water
{
	namespace render
	{
		GLuint get_shader_type(ShaderType& shader_type);
		bool inline check_location(const std::string& name, GLuint loc)
		{
			if (loc == 0xFFFFFFFF)
			{
				log_error("[LOCATION]illegal location of name %s", name.c_str());
				return false;
			}
			return true;
		}
		ShaderObject ProgramManagerOpenGL::load_shader(ShaderType shader_type, const std::string& file_path)
		{
			ShaderMap::iterator rst = m_shader_map.find(file_path);
			if (rst != m_shader_map.end())
			{
				return rst->second;
			}
			
			auto abs_path = filesystem::FileSystem::get_instance()->get_absolute_path(file_path.c_str());
			std::ifstream fs(abs_path, std::ios::in);
			std::string shader_code;
			if (fs.is_open())
			{
				std::stringstream ss;
				ss << fs.rdbuf();
				shader_code = ss.str();
				fs.close();
			}
			const char* buffer = shader_code.c_str();
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
				log_warn("Compile Shader(%s) failed", file_path.c_str());
				return -1;
			}
			else
			{
				m_shader_map[file_path] = shader;
				return shader;
			}
		}
		
		ProgramPtr ProgramManagerOpenGL::load_program(const std::string& vertex_shader_path, const std::string& geom_shader_path, const std::string& frag_shader_path)
		{
			ProgramPtr ptr = std::make_shared<RenderProgramOpenGL>();
			ptr->init(vertex_shader_path, geom_shader_path, frag_shader_path);
			return ptr;
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
				return GL_GEOMETRY_SHADER;
			default:
				break;
			}
			return 0;
		}

		RenderProgramOpenGL::RenderProgramOpenGL()
		{
		}

		RenderProgramOpenGL::~RenderProgramOpenGL()
		{
			glDeleteProgram(m_program);
		}

		bool RenderProgramOpenGL::init(const std::string& vertex_shader_path, const std::string& geom_shader_path, const std::string& frag_shader_path)
		{
			m_shader_paths[0] = vertex_shader_path;
			m_shader_paths[1] = geom_shader_path;
			m_shader_paths[2] = frag_shader_path;
			return true;
		}

		bool RenderProgramOpenGL::init(ShaderObject vertex_shader, ShaderObject geom_shader, ShaderObject frag_shader)
		{
			glAttachShader(m_program, vertex_shader);
			glAttachShader(m_program, geom_shader);
			glAttachShader(m_program, frag_shader);
			glLinkProgram(m_program);
			// todo check is link success
			return true;
		}

		bool RenderProgramOpenGL::init(ShaderObject vertex_shader, ShaderObject frag_shader)
		{
			glAttachShader(m_program, vertex_shader);
			glAttachShader(m_program, frag_shader);
			glLinkProgram(m_program);
			// todo check is link success
			return true;
		}

		bool RenderProgramOpenGL::set_uniform_config(UniformTypeMap& uniform_map)
		{
			m_uniform_map = uniform_map;
			m_location_inited = false;
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string & name, math3d::Matrix* mat)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniformMatrix4fv(location, 1, GL_TRUE, mat->getData());
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string & name, math3d::Vector3* vec3)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniform3fv(location, 1, vec3->getData());
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string & name, math3d::Vector2* vec2)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniform2fv(location, 1, vec2->getData());
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string & name, int* val)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniform1i(location, *val);
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string & name, float* val)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniform1f(location, *val);
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string& name, MaterialParam::MatrixArray* mtxArray)
		{
			auto rst = m_location_map.find(name);
			if (rst == m_location_map.end()) return false;
			auto location = rst->second;
			glUniformMatrix4fv(location, mtxArray->size(), GL_TRUE, (*mtxArray)[0].getData());
			return true;
		}

		bool RenderProgramOpenGL::setUniform(const std::string& name, StructParam* structParam)
		{
			if (m_uniform_map.find(name) == m_uniform_map.end()) return false;
			UniformTypeMap uMap = structParam->getUniformTypeMap();
			update_location(uMap);
			apply_parameters(*structParam);
			return true;
		}

		bool RenderProgramOpenGL::use_program()
		{
			if (!m_inited) real_init();
			glUseProgram(m_program);
			GL_CHECK_ERROR
			return true;
		}

		void RenderProgramOpenGL::apply_parameters(const MaterialParamMap& param_map)
		{
			if (!m_inited) real_init();
			if (!m_location_inited) update_location(m_uniform_map);

			// set textuers
			auto device = get_device();
			TextureUnit tex_units[] = { TEXTURE_UNIT_0, TEXTURE_UNIT_1, TEXTURE_UNIT_2, TEXTURE_UNIT_3, TEXTURE_UNIT_4, TEXTURE_UNIT_5};
			GLuint texIndex = 0;

			for(auto iter = param_map.m_paramMap.begin(); iter != param_map.m_paramMap.end(); ++iter)
			{
				std::string name = iter->first;
				MaterialParam param = iter->second;
				if (!param.isInited())
				{
					log_error("Material param %s is not inited", name);
					continue;
				}

				switch (param.m_type)
				{
					case UniformType::TypeFloat :
						setUniform(name, param.m_float);
						break;
					case UniformType::TypeInt:
						setUniform(name, param.m_int);
						break;
					case UniformType::TypeMatrix:
						setUniform(name, param.m_mtx);
						break;
					case UniformType::TypeVector2:
						setUniform(name, param.m_vec2);
						break;
					case UniformType::TypeVector3:
						setUniform(name, param.m_vec3);
						break;
					case UniformType::TypeCubeMap:
					case UniformType::TypeSampler2D:
						param.m_tex->m_texPtr->bind(tex_units[texIndex]);
						setUniform(name, (int*)&texIndex);
						++texIndex;
						break;
					case UniformType::TypeMatrixArray:
						setUniform(name, param.m_mtxArray);
						break;
					case UniformType::TypeStruct:
						setUniform(name, param.m_struct);
						break;
					default:
						log_error("Unkown type: %d", param.m_type);
						break;
				}
			}
			GL_CHECK_ERROR
		}
		bool RenderProgramOpenGL::real_init()
		{
			m_inited = true;
			m_program = glCreateProgram();
			auto vertex_shader_path = m_shader_paths[0], geom_shader_path = m_shader_paths[1], frag_shader_path = m_shader_paths[2];
			if (vertex_shader_path != "")
			{
				ShaderObject obj = get_device()->get_program_manager()->load_shader(VertexShader, vertex_shader_path);
				if (obj != UNDEFINED_SHADER)
				{
					glAttachShader(m_program, obj);
				}
			}
			if (geom_shader_path != "")
			{
				auto obj = get_device()->get_program_manager()->load_shader(GeometryShader, geom_shader_path);
				if (obj != UNDEFINED_SHADER)
				{
					glAttachShader(m_program, obj);
				}
			}
			if (frag_shader_path != "")
			{
				auto obj = get_device()->get_program_manager()->load_shader(FragmentShader, frag_shader_path);
				if (obj != UNDEFINED_SHADER)
				{
					glAttachShader(m_program, obj);
				}
			}
			glLinkProgram(m_program);
			// check program link success
			GLint result = GL_FALSE;
			GLint log_length = 0;
			glGetProgramiv(m_program, GL_LINK_STATUS, &result);
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &log_length);
			if (log_length > 0)
			{
				char* msg = new char[log_length];
				glGetProgramInfoLog(m_program, log_length, NULL, msg);
				log_info(msg);
				delete[] msg;
			}
			return false;
		}
		bool RenderProgramOpenGL::update_location(UniformTypeMap & uniform_map)
		{
			m_location_inited = true;
			for (auto iter = uniform_map.begin(); iter != uniform_map.end(); ++iter)
			{
				auto name = iter->first;
				if (m_location_map.find(name) != m_location_map.end() || m_invalid_map.find(name) != m_invalid_map.end())
				{
					continue;
				}
				if (iter->second == UniformType::TypeStruct) 
				{
					continue;
				}
				GLuint location = glGetUniformLocation(m_program, name.c_str());
				if (check_location(name, location))
				{
					m_location_map[name] = location;
				}
				else
				{
					m_invalid_map.insert(name);
				}
			}
			return true;
		}
	}
}
