#ifndef WATER_DRAW_COMMAND_H
#define WATER_DRAW_COMMAND_H
#include "render_const.h"

namespace water
{
	namespace render
	{
		struct DrawCommand
		{
			DrawMode draw_mode = {TRIANGLES};
		};

	}
}

#endif // !WATER_DRAW_COMMAND_H
