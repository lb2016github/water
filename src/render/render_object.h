#ifndef WATER_RENDER_OBJECT_H
#define WATER_RENDER_OBJECT_H
#include "common/common.h"
#include <memory>
#include "render/render.h"
#include "render/material.h"
#include "render/render_const.h"
#include "mesh.h"
#include "draw_command.h"

namespace water
{
	namespace render
	{
		WaterInterface IRenderable 
		{
			virtual MaterialPtr get_material() = 0;
			virtual MeshDataPtr get_mesh() = 0;
			virtual DrawCommand get_draw_command() = 0;
		};
	}
}

#endif // !WATER_RENDER_OBJECT_H
