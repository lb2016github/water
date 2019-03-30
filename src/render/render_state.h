#ifndef WATER_RENDER_STATE_h
#define WATER_RENDER_STATE_h
#include "render/render_state_info.h"
#include "common/common.h"

namespace water {
	namespace render {
		WaterInterface RenderState{
			DepthStateInfo depth;
			StencilStateInfo stencil;
			RasterizeStateInfo raster;
			BlendStateInfo blend;

			virtual void apply_depth_state(DepthStateInfo* info = nullptr) = 0;
			virtual void apply_stencil_state(StencilStateInfo* info = nullptr) = 0;
			virtual void apply_rasterize_state(RasterizeStateInfo* info = nullptr) = 0;
			virtual void apply_blend_state(BlendStateInfo* info = nullptr) = 0;
		};


		class RenderStateOpenGL : public RenderState {
		public:
			virtual void apply_depth_state(DepthStateInfo* info = nullptr);
			virtual void apply_stencil_state(StencilStateInfo* info = nullptr);
			virtual void apply_rasterize_state(RasterizeStateInfo* info = nullptr);
			virtual void apply_blend_state(BlendStateInfo* info = nullptr);
		};

	}
}

#endif
