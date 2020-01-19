#ifndef WATER_STRUCT_PARAM_H
#define WATER_STRUCT_PARAM_H
#include "material_param.h"
#include "material_param.h"

namespace water
{
	namespace render
	{
		class MaterialParamMap;

		/*
		parameter of stuct, which consists of mutiple params, such as light
		*/
		struct StructParam: public MaterialParamMap
		{
			/*
			get uniform type map
			*/
			UniformTypeMap getUniformTypeMap();
		};

	}
}
#endif // WATER_STRUCT_PARAM_H

