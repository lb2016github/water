#ifndef WATER_RENDER_PROGRAM_OPENGL_H
#define WATER_RENDER_PROGRAM_OPENGL_H
#include "common/common.h"
#include "render/render.h"
#include "render/render_program.h"
#include <map>
#include <string>
#include "glad/glad.h"

namespace water {
	namespace render {

		class RenderProgramOpenGL: public IRenderProgram
		{
		public:
			RenderProgramOpenGL();
			~RenderProgramOpenGL();
			// init program
			virtual bool init(const char* vertex_shader_path, const char* geom_shader_path, const char* frag_shader_path);
			virtual bool init(ShaderObject vertex_shader, ShaderObject geom_shader, ShaderObject frag_shader);
			virtual bool init(ShaderObject vertex_shader, ShaderObject frag_shader);
			// set uniform
			virtual bool set_uniform(const std::string& name, math3d::Matrix& mat);
			virtual bool set_uniform(const std::string& name, math3d::Vector3& vec3);
			virtual bool set_uniform(const std::string& name, math3d::Vector2& vec2);
			virtual bool set_uniform(const std::string& name, int val);
			virtual bool set_uniform(const std::string& name, float val);
			// set uniform config
			virtual bool set_uniform_config(ParamTypeMap& uniform_map);
			virtual bool set_attribute_config(ParamTypeMap& attribute_map);
			// use program
			virtual bool use_program();
		private:
			GLuint m_program;
			ParamTypeMap m_uniform_map;
			ParamTypeMap m_attribute_map;
		};

		class ProgramManagerOpenGL: public IProgramManager
		{
			virtual ShaderObject load_shader(ShaderType shader_type, const char* file_path);
			virtual ProgramPtr load_program(const char* vertex_shader_path, const char* geom_shader_path = "", const char* frag_shader_path = "");
		private:
			ShaderMap m_shader_map;
		};
	}
}

#endif // !WATER_RENDER_PROGRAM_OPENGL_H
