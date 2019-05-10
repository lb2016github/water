#ifndef WATER_RENDER_PROGRAM_H
#define WATER_RENDER_PROGRAM_H
#include "common/common.h"
#include "render/render_state_info.h"
#include "render/technique_common.h"
#include <string>
#include "math3d/math3d.hpp"
#include <memory>

namespace water
{
	namespace render
	{
		WaterInterface IProgramManager;
		WaterInterface IRenderProgram;
		typedef std::shared_ptr<IRenderProgram> ProgramPtr;
		typedef unsigned int ShaderObject;

		/*
		management programs
		*/
		WaterInterface IProgramManager
		{
			virtual ShaderObject load(ShaderType& shader_type, const char* file_path) = 0;
			virtual ProgramPtr load_program(const char* vertex_shader_path, const char* geom_shader_path = "", const char* frag_shader_pash = "") = 0;
			static IProgramManager* get_instance();
		};

		/*
		* the interface of render program
		*/
		WaterInterface IRenderProgram
		{
			// atach shaders
			virtual bool attach_shader(ShaderType& shader_type, const char* file_path) = 0;
			virtual bool attach_shader(ShaderType& shader_type, ShaderObject& shader_obj) = 0;
			// set uniform
			virtual bool set_uniform(const std::string& name, math3d::Matrix& mat) = 0;
			virtual bool set_uniform(const std::string& name, math3d::Vector3& vec3) = 0;
			virtual bool set_uniform(const std::string& name, math3d::Vector2& vec2) = 0;
			virtual bool set_uniform(const std::string& name, int& val) = 0;
			// set uniform config
			virtual bool set_uniform_config(ParamTypeMap& uniform_map) = 0;
			virtual bool set_attribute_config(ParamTypeMap& attribute_map) = 0;
			// use program
			virtual bool use_program() = 0;;
		};

	}
}

#endif // !WATER_RENDER_PROGRAM_H 