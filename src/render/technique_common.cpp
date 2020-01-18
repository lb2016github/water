#include "technique_common.h"

namespace water {
	namespace render {
		extern std::map<std::string, StencilOperation> CONFIG_StencilOperation = {
			{"STENCILOP_KEEP", STENCILOP_KEEP},
			{"STENCILOP_ZERO", STENCILOP_ZERO},
			{"STENCILOP_REPLACE", STENCILOP_REPLACE},
			{"STENCILOP_INCRWRAP", STENCILOP_INCRWRAP},
			{"STENCILOP_DECRWRAP", STENCILOP_DECRWRAP},
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

		std::map<std::string, UniformType> CONFIG_uniform_type =
		{
			{UNIFORM_VALUE_TYPE_VECTOR3, UniformType::TypeVector3},
			{UNIFORM_VALUE_TYPE_VECTOR2, UniformType::TypeVector2},
			{UNIFORM_VALUE_TYPE_MATRIX, UniformType::TypeMatrix},
			{UNIFORM_VALUE_TYPE_FLOAT, UniformType::TypeFloat},
			{UNIFORM_VALUE_TYPE_INT, UniformType::TypeInt},
			{UNIFORM_VALUE_TYPE_SAMPLE2D, UniformType::TypeSampler2D},
			{UNIFORM_VALUE_TYPE_CUBEMAP, UniformType::TypeCubeMap},
			{UNIFORM_VALUE_TYPE_MATRIX_ARRAY, UniformType::TypeMatrixArray},
			{UNIFORM_VALUE_TYPE_STRUCT, UniformType::TypeStuct},
		};

		std::map<std::string, SemanticType> CONFIG_Semantic =
		{
			{"None", SemanticNone},
			{"WVP", SemanticWVP},
			{"VP", SemanticVP},
			{"WORLD", SemanticWorld},
			{"CAMERA_POSITION", SemanticCameraPosition},
			{"LIGHT", SemanticLight},
			{"SHADOW_MAP_VP", SemanticShadowMapVP},
			{"SHADOW_MAP_TEXTURE", SemanticShadowMapTexture},
			{"ENV_MAP_TEXTURE", SemanticEnvMap},
			{"SKIN_MATRIX", SemanticSkinMatrix},
		};
	}
}


