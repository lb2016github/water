#ifndef WATER_TECHNIQUE_LOADER_CONFIG
#define WATER_TECHNIQUE_LOADER_CONFIG
#include "render\render_state_info.h"
#include <map>
#include <string>
#include "math3d/math3d.hpp"

namespace water {
	namespace render {
		std::map<std::string, StencilOperation> CONFIG_StencilOperation = {
			{"STENCILOP_KEEP", STENCILOP_KEEP},
			{"STENCILOP_ZERO", STENCILOP_ZERO},
			{"STENCILOP_REPLACE", STENCILOP_REPLACE},
			{"STENCILOP_INCRSAT", STENCILOP_INCRSAT},
			{"STENCILOP_DECRSAT", STENCILOP_DECRSAT},
			{"STENCILOP_INVERT", STENCILOP_INVERT},
			{"STENCILOP_INCR", STENCILOP_INCR},
			{"STENCILOP_DECR", STENCILOP_DECR},
		};

		std::map<std::string, CompareFunc> CONFIG_CompareFunc = {
			{"CMP_NEVER", CMP_NEVER},
			{"CMP_LESS", CMP_LESS},
			{"CMP_EQUAL", CMP_EQUAL},
			{"CMP_LESS_EQUAL", CMP_LESS_EQUAL},
			{"CMP_GREATER", CMP_GREATER},
			{"CMP_NOTEQUAL", CMP_NOTEQUAL},
			{"CMP_GREATER_EQUAL", CMP_GREATER_EQUAL},
			{"CMP_ALWAYS", CMP_ALWAYS},
		};

		std::map<std::string, ClearMode> CONFIG_ClearMode = {
			{"CLEAR_NONE", CLEAR_NONE},
			{"CLEAR_COLOR", CLEAR_COLOR},
			{"CLEAR_DEPTH", CLEAR_DEPTH},
			{"CLEAR_STENCIL", CLEAR_STENCIL},
			{"CLEAR_ALL", CLEAR_ALL},
			{"CLEAR_COLOR_DEPTH", CLEAR_COLOR_DEPTH},
		};

		std::map<std::string, FillMode> CONFIG_FillMode = {
			{"FILL_POINT", FILL_POINT},
			{"FILL_WIREFRAME", FILL_WIREFRAME},
			{"FILL_SOLID", FILL_SOLID},
		};

		std::map<std::string, CullMode> CONFIG_CullMode = {
			{"CULL_NONE", CULL_NONE},
			{"CULL_FRONT", CULL_FRONT},
			{"CULL_BACK", CULL_BACK},
		};

		std::map<std::string, BlendOperation> CONFIG_BlendOperation = {
			{"BLENDOP_ADD", BLENDOP_ADD},
			{"BLENDOP_SUBTRACT", BLENDOP_SUBTRACT},
			{"BLENDOP_REV_SUBTRACT", BLENDOP_REV_SUBTRACT},
			{"BLENDOP_MIN", BLENDOP_MIN},
			{"BLENDOP_MAX", BLENDOP_MAX},
		};

		std::map<std::string, BlendFactor> CONFIG_BlendFactor = {
			{"BLEND_ZERO", BLEND_ZERO},
			{"BLEND_ONE", BLEND_ONE},
			{"BLEND_SRC_COLOR", BLEND_SRC_COLOR},
			{"BLEND_INVS_SRC_COLOR", BLEND_INVS_SRC_COLOR},
			{"BLEND_SRC_ALPHA", BLEND_SRC_ALPHA},
			{"BLEND_INVS_SRC_ALPHA", BLEND_INVS_SRC_ALPHA},
			{"BLEND_DST_ALPHA", BLEND_DST_ALPHA},
			{"BLEND_INV_DST_ALPHA", BLEND_INV_DST_ALPHA},
			{"BLEND_DST_COLOR", BLEND_DST_COLOR},
			{"BLEND_INV_DST_COLOR", BLEND_INV_DST_COLOR},
			{"BLEND_SRC_ALPHA_SAT", BLEND_SRC_ALPHA_SAT},
			{"BLEND_CONSTANT", BLEND_CONSTANT},
			{"BLEND_INV_CONSTANT", BLEND_INV_CONSTANT},
		};

		// represent value of varial types
		union ParamValue
		{
			math3d::Vector3 vec3;
			math3d::Vector2 vec2;
			math3d::Matrix mat;
			float float_1;
			int int_1;
		};

		enum ParamValueType
		{
			TypeVector3,
			TypeVector2,
			TypeMatrix,
			TypeFloat,
			TypeInt,
		};

		typedef std::map<std::string, ParamValue> ParamValueMap;
		typedef std::map<std::string, ParamValueType> ParamTypeMap;

		std::map<std::string, ParamValueType> CONFIG_param_type =
		{
			{"Vector3", TypeVector3},
			{"Vector2", TypeVector2},
			{"Matrix", TypeMatrix},
			{"Float", TypeFloat},
			{"Int", TypeInt},
		};
	}
}



#endif // !WATER_TECHNIQUE_LOADER_CONFIG
