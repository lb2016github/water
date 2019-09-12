#include "render/opengl/render_program_opengl.h"
#include "filesystem\filesystem.h"
#include "glad/glad.h"
#include "common/log.h"
#include "render/material.h"
#include "render/device.h"
#include <sstream>

namespace water
{
	namespace render
	{
		GLuint get_shader_type(ShaderType& shader_type);
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
				return GL_FRAGMENT_SHADER;
			default:
				break;
			}
			return 0;
		}

		RenderProgramOpenGL::RenderProgramOpenGL()
		{
			m_program = glCreateProgram();
		}

		RenderProgramOpenGL::~RenderProgramOpenGL()
		{
			glDeleteProgram(m_program);
		}

		bool RenderProgramOpenGL::init(const std::string& vertex_shader_path, const std::string& geom_shader_path, const std::string& frag_shader_path)
		{
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
			// todo check is link success
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

		bool RenderProgramOpenGL::set_uniform(const std::string & name, math3d::Matrix & mat)
		{
			GLuint location = glGetUniformLocation(m_program, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
			return true;
		}

		bool RenderProgramOpenGL::set_uniform(const std::string & name, math3d::Vector3 & vec3)
		{
			GLuint location = glGetUniformLocation(m_program, name.c_str());
			glUniform3fv(location, 1, &vec3[0]);
			return true;
		}

		bool RenderProgramOpenGL::set_uniform(const std::string & name, math3d::Vector2 & vec2)
		{
			GLuint location = glGetUniformLocation(m_program, name.c_str());
			glUniform2fv(location, 1, &vec2[0]);
			return true;

		}

		bool RenderProgramOpenGL::set_uniform(const std::string & name, int val)
		{
			GLuint location = glGetUniformLocation(m_program, name.c_str());
			glUniform1i(location, val);
			return true;
		}

		bool RenderProgramOpenGL::set_uniform(const std::string & name, float val)
		{
			GLuint location = glGetUniformLocation(m_program, name.c_str());
			glUniform1f(location, val);
			return true;
		}

		bool RenderProgramOpenGL::set_uniform_config(ParamTypeMap & uniform_map)
		{
			m_uniform_map = uniform_map;
			return true;
		}

		bool RenderProgramOpenGL::set_attribute_config(ParamTypeMap & attribute_map)
		{
			m_attribute_map = attribute_map;
			return true;
		}

		bool RenderProgramOpenGL::use_program()
		{
			glUseProgram(m_program);
			return true;
		}

		void RenderProgramOpenGL::apply_parameters(const ParameterMap& param_map)
		{
			for (auto param : param_map.m_value_map)
			{
				std::string name = param.first;
				ParamValue pv = param.second;
				ParamValueType pvt = param_map.get_value_type(name);
				switch (pvt)
				{
				case water::render::TypeNone:
					break;
				case water::render::TypeVector3:
					set_uniform(name, pv.vec3);
					break;
				case water::render::TypeVector2:
					set_uniform(name, pv.vec2);
					break;
				case water::render::TypeMatrix:
					set_uniform(name, pv.mat);
					break;
				case water::render::TypeFloat:
					set_uniform(name, pv.float_1);
					break;
				case water::render::TypeInt:
					set_uniform(name, pv.int_1);
					break;
				default:
					break;
				}
			}
		}

	}
}
