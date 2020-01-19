#ifndef WATER_RENDER_PROGRAM_H
#define WATER_RENDER_PROGRAM_H
#include "common/common.h"
#include <string>
#include "math3d/math3d.hpp"
#include <memory>
#include "render/render.h"
#include "material_param.h"

namespace water
{
	namespace render
	{
		/*
		management programs
		*/
		WaterInterface IProgramManager
		{
			virtual ShaderObject load_shader(ShaderType shader_type, const std::string& file_path) = 0;
			virtual ProgramPtr load_program(const std::string& vertex_shader_path, const std::string& geom_shader_path = "", const std::string& frag_shader_pash = "") = 0;
		};


		/*
		* the interface of render program
		*/
		WaterInterface IRenderProgram
		{
			// init program
			virtual bool init(const std::string& vertex_shader_path, const std::string& geom_shader_path, const std::string& frag_shader_path) = 0;
			virtual bool init(ShaderObject vertex_shader, ShaderObject geom_shader, ShaderObject frag_shader) = 0;
			virtual bool init(ShaderObject vertex_shader, ShaderObject frag_shader) = 0;
			// set uniform config
			virtual bool set_uniform_config(UniformTypeMap& uniform_map) = 0;
			// use program
			virtual bool use_program() = 0;
			// apply parameters
			virtual void apply_parameters(const MaterialParamMap& param_map) = 0;
		};

	}
}

#endif // !WATER_RENDER_PROGRAM_H 