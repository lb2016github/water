#ifndef WATER_TECHNIQUE_LOADER_CONFIG
#define WATER_TECHNIQUE_LOADER_CONFIG
#include "render\render_const.h"
#include <map>
#include <string>
#include "math3d/math3d.hpp"

namespace water {
	namespace render {
		extern std::map<std::string, StencilOperation> CONFIG_StencilOperation;
		extern std::map<std::string, CompareFunc> CONFIG_CompareFunc;

		extern std::map<std::string, ClearMode> CONFIG_ClearMode;

		extern std::map<std::string, FillMode> CONFIG_FillMode;

		extern std::map<std::string, CullMode> CONFIG_CullMode;

		extern std::map<std::string, BlendOperation> CONFIG_BlendOperation;

		extern std::map<std::string, BlendFactor> CONFIG_BlendFactor;

		/*
		types of uniform
		*/
		enum class UniformType
		{
			TypeNone,
			TypeVector3,
			TypeVector2,
			TypeMatrix,
			TypeFloat,
			TypeInt,
			TypeSampler2D,
			TypeCubeMap,
			/* array of matrix */
			TypeMatrixArray,
			TypeStruct,
		};

		typedef std::map<std::string, UniformType> UniformTypeMap;

		constexpr auto UNIFORM_VALUE_TYPE_MATRIX = "Matrix";
		constexpr auto UNIFORM_VALUE_TYPE_VECTOR3 = "Vector3";
		constexpr auto UNIFORM_VALUE_TYPE_VECTOR2 = "Vector2";
		constexpr auto UNIFORM_VALUE_TYPE_FLOAT = "Float";
		constexpr auto UNIFORM_VALUE_TYPE_INT = "Int";
		constexpr auto UNIFORM_VALUE_TYPE_SAMPLE2D = "Sampler2D";
		constexpr auto UNIFORM_VALUE_TYPE_CUBEMAP = "CubeMap";
		constexpr auto UNIFORM_VALUE_TYPE_MATRIX_ARRAY = "MatrixArray";
		constexpr auto UNIFORM_VALUE_TYPE_STRUCT = "Struct";

		extern std::map<std::string, UniformType> CONFIG_uniform_type;

		enum SemanticType
		{
			SemanticNone,	// no semantic
			SemanticWVP,	// matrix of wvp
			SemanticVP,		// matrix of vp
			SemanticWorld,	// matrix of world
			SemanticCameraPosition, // position of camera
			SemanticLight,	// light
			SemanticShadowMapVP,	// vp of shadow map
			SemanticShadowMapTexture,	// texture of shadow map
			SemanticEnvMap,	// env map
			SemanticSkinMatrix,	// skin matrix
		};
		extern std::map<std::string, SemanticType> CONFIG_Semantic;
	}
}



#endif // !WATER_TECHNIQUE_LOADER_CONFIG
