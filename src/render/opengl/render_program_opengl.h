#ifndef WATER_RENDER_PROGRAM_OPENGL_H
#define WATER_RENDER_PROGRAM_OPENGL_H
#include "common/common.h"
#include "render/render.h"
#include "render/render_program.h"
#include <map>
#include <set>
#include <string>
#include "glad/glad.h"
#include "render/light.h"
#include <array>

namespace water {
	namespace render {

		class RenderProgramOpenGL: public IRenderProgram
		{
		public:
			RenderProgramOpenGL();
			~RenderProgramOpenGL();
			// init program
			virtual bool init(const std::string& vertex_shader_path, const std::string& geom_shader_path, const std::string& frag_shader_path);
			virtual bool init(ShaderObject vertex_shader, ShaderObject geom_shader, ShaderObject frag_shader);
			virtual bool init(ShaderObject vertex_shader, ShaderObject frag_shader);
			// set uniform config
			virtual bool set_uniform_config(ParamTypeMap& uniform_map);
			virtual bool set_attribute_config(ParamTypeMap& attribute_map);
			// use program
			virtual bool use_program();
			// apply parameters
			virtual void apply_parameters(const ParameterMap& param_map);
		public:
			// set uniform
			virtual bool set_uniform(const std::string& name, math3d::Matrix& mat);
			virtual bool set_uniform(const std::string& name, math3d::Vector3& vec3);
			virtual bool set_uniform(const std::string& name, math3d::Vector2& vec2);
			virtual bool set_uniform(const std::string& name, int val);
			virtual bool set_uniform(const std::string& name, float val);
		private:
			bool real_init();
			bool update_location(ParamTypeMap& uniform_map);
			bool set_light(LightParamMap& light_param);

		private:
			GLuint m_program;
			std::array<std::string, 3> m_shader_paths;
			ParamTypeMap m_uniform_map;
			ParamTypeMap m_attribute_map;
			std::map<std::string, GLuint> m_location_map;
			std::set<std::string> m_invalid_map;
			bool m_inited{ false }, m_location_inited{ false };
		};

		class ProgramManagerOpenGL: public IProgramManager
		{
			virtual ShaderObject load_shader(ShaderType shader_type, const std::string& file_path);
			virtual ProgramPtr load_program(const std::string& vertex_shader_path, const std::string& geom_shader_path = "", const std::string& frag_shader_path = "");
		private:
			ShaderMap m_shader_map;
		};
	}
}

#endif // !WATER_RENDER_PROGRAM_OPENGL_H
