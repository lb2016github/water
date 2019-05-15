#ifndef WATER_RENDER_STATE_MGR_OPENGL_H
#define WATER_RENDER_STATE_MGR_OPENGL_H
#include "render/render_state_info.h"
#include "common/common.h"
#include "render/render_state.h"
#include "render/render_state.h"

namespace water {
	namespace render {
		class RenderStateManagerOpenGL : public IRenderStateManager {
		public:
			virtual void apply_depth_state(const DepthStateInfo& info);
			virtual void apply_stencil_state(const StencilStateInfo& info);
			virtual void apply_rasterize_state(const RasterizeStateInfo& info);
			virtual void apply_blend_state(const BlendStateInfo& info);
		private:
			RenderStateInfo m_cur_state;	// cur render state
		};

	}
}

#endif
