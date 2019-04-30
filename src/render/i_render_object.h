#ifndef WATER_I_RENDER_OBJECT_H
#define WATER_I_RENDER_OBJECT_H
#include "common/common.h"
#include "render/i_material.h"

namespace water
{
	namespace render
	{
		WaterInterface IRenderObject
		{
			virtual void set_material(IMaterial* material) = 0;
			virtual IMaterial* get_material() = 0;
			virtual void render() = 0;
		};
	}
}

#endif // !WATER_I_RENDER_OBJECT_H
