#ifndef WATER_RENDER_PROGRAM_H
#define WATER_RENDER_PROGRAM_H
#include "common/common.h"
#include <string>
#include "math3d/math3d.hpp"
#include <memory>
#include "render/render.h"

namespace water
{
	namespace render
	{
		/*
		management programs
		*/
		WaterInterface IProgramManager
		{
			virtual ShaderObject load_shader(ShaderType shader_type, const char* file_path) = 0;
			virtual ProgramPtr load_program(const char* vertex_shader_path, const char* geom_shader_path = "", const char* frag_shader_pash = "") = 0;
		};


		IProgramManager* get_program_manager();

		/*
		* the interface of render program
		*/
		WaterInterface IRenderProgram
		{
			// init program
			virtual bool init(const char* vertex_shader_path, const char* geom_shader_path, const char* frag_shader_path) = 0;
			virtual bool init(ShaderObject vertex_shader, ShaderObject geom_shader, ShaderObject frag_shader) = 0;
			virtual bool init(ShaderObject vertex_shader, ShaderObject frag_shader) = 0;
			// set uniform
			virtual bool set_uniform(const std::string& name, math3d::Matrix& mat) = 0;
			virtual bool set_uniform(const std::string& name, math3d::Vector3& vec3) = 0;
			virtual bool set_uniform(const std::string& name, math3d::Vector2& vec2) = 0;
			virtual bool set_uniform(const std::string& name, int val) = 0;
			virtual bool set_uniform(const std::string& name, float val) = 0;
			// set uniform config
			virtual bool set_uniform_config(ParamTypeMap& uniform_map) = 0;
			virtual bool set_attribute_config(ParamTypeMap& attribute_map) = 0;
			// use program
			virtual bool use_program() = 0;
		};

	}
}

#endif // !WATER_RENDER_PROGRAM_H 