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
#include "render/material_param.h"
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
			virtual bool set_uniform_config(UniformTypeMap& uniform_map);
			// use program
			virtual bool use_program();
			// apply parameters
			virtual void apply_parameters(const MaterialParamMap& param_map);
		public:
			// set uniform
			virtual bool setUniform(const std::string& name, math3d::Matrix* mat);
			virtual bool setUniform(const std::string& name, math3d::Vector3* vec3);
			virtual bool setUniform(const std::string& name, math3d::Vector2* vec2);
			virtual bool setUniform(const std::string& name, int* val);
			virtual bool setUniform(const std::string& name, float* val);
			virtual bool setUniform(const std::string& name, MaterialParam::MatrixArray* mtxArray);
			virtual bool setUniform(const std::string& name, BaseStructParam* baseStructParam);
		private:
			bool real_init();
			/*
			init location of uniform parameters
			*/
			bool update_location(UniformTypeMap& uniform_map);

		private:
			GLuint m_program;
			std::array<std::string, 3> m_shader_paths;
			UniformTypeMap m_uniform_map;
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
