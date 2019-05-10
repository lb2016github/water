#ifndef WATER_I_DEVICE_H
#define WATER_I_DEVICE_H
#include "render/render_state_info.h"
#include "common/common.h"
#include "math3d/math3d.hpp"
#include <string>

namespace water
{
	namespace render
	{
		WaterInterface IRenderStateManager;
		WaterInterface IDevice;


		/*
		* Mangagement render state.
		*/
		WaterInterface IRenderStateManager
		{
			virtual void apply(const RenderState& render_state) 
			{
				apply_depth_state(render_state.depth);
				apply_stencil_state(render_state.stencil);
				apply_rasterize_state(render_state.raster);
				apply_blend_state(render_state.blend);
			}
			virtual void apply_depth_state(const DepthStateInfo& info) = 0;
			virtual void apply_stencil_state(const StencilStateInfo& info) = 0;
			virtual void apply_rasterize_state(const RasterizeStateInfo& info) = 0;
			virtual void apply_blend_state(const BlendStateInfo& info) = 0;
		};
	}
}

#endif // !WATER_DEVICE_H
