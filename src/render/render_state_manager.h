#ifndef WATER_RENDER_STATE_MGR_H
#define WATER_RENDER_STATE_MGR_H
#include "render/render_state_info.h"
#include "common/common.h"

namespace water {
	namespace render {
		WaterInterface RenderStateManager{
			virtual void apply(const RenderState& render_state) {
				apply_depth_state(render_state.depth);
				apply_stencil_state(render_state.stencil);
				apply_rasterize_state(render_state.raster);
				apply_blend_state(render_state.blend);
			}
			virtual void apply_depth_state(const DepthStateInfo& info) = 0;
			virtual void apply_stencil_state(const StencilStateInfo& info) = 0;
			virtual void apply_rasterize_state(const RasterizeStateInfo& info) = 0;
			virtual void apply_blend_state(const BlendStateInfo& info) = 0;

			RenderState m_cur_state;	// cur render state
		};


		class RenderStateManagerOpenGL : public RenderStateManager {
		public:
			virtual void apply_depth_state(const DepthStateInfo& info);
			virtual void apply_stencil_state(const StencilStateInfo& info);
			virtual void apply_rasterize_state(const RasterizeStateInfo& info);
			virtual void apply_blend_state(const BlendStateInfo& info);
		};

	}
}

#endif
