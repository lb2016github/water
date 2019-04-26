#ifndef WATER_RENDER_STATE_INFO_H
#define WATER_RENDER_STATE_INFO_H

namespace water {
namespace render {
	enum StencilOperation {
		STENCILOP_KEEP, ///< Do not update the entry in the stencil buffer. This is the default value. 
		STENCILOP_ZERO, ///< Set the stencil-buffer entry to 0. 
		STENCILOP_REPLACE, ///< Replace the stencil-buffer entry with a reference value.
		STENCILOP_INCRSAT, ///< Increment the stencil-buffer entry, clamping to the maximum value.
		STENCILOP_DECRSAT, ///< Decrement the stencil-buffer entry, clamping to zero.
		STENCILOP_INVERT, ///< Invert the bits in the stencil-buffer entry.
		STENCILOP_INCR,///< Increment the stencil-buffer entry, wrapping to zero if the new value exceeds the maximum value.
		STENCILOP_DECR, ///< Decrement the stencil-buffer entry, wrapping to the maximum value if the new value is less than zero. 
	};

	// �ȽϺ���
	enum CompareFunc {
		CMP_NEVER,		// ��Զʧ��
		CMP_LESS,		// С��
		CMP_EQUAL,		// ����
		CMP_LESS_EQUAL,	// С�ڵ���
		CMP_GREATER,	// ����
		CMP_NOTEQUAL,	// ������
		CMP_GREATER_EQUAL,	// ���ڵ���
		CMP_ALWAYS		// ��Զ�ɹ�
	};

	enum ClearMode{
		CLEAR_NONE = 0,
		CLEAR_COLOR = 1,
		CLEAR_DEPTH = 2,
		CLEAR_STENCIL = 4,
		CLEAR_ALL = CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL,
		CLEAR_COLOR_DEPTH = CLEAR_COLOR | CLEAR_DEPTH
	};

	enum FillMode {
		FILL_POINT,		// ��
		FILL_WIREFRAME,	// �߿�
		FILL_SOLID,		// ʵ��
	};

	enum CullMode{
		CULL_NONE,
		CULL_FRONT,
		CULL_BACK,
	};

	enum BlendOperation {
		BLENDOP_ADD,			// src + dst
		BLENDOP_SUBTRACT,		// src - dst
		BLENDOP_REV_SUBTRACT,	// dst - src
		BLENDOP_MIN,			// min(src, dst)
		BLENDOP_MAX,			// max(src, dst)
	};
	enum BlendFactor {
		BLEND_ZERO = 1,		// color(0, 0, 0, 0)
		BLEND_ONE,			// color(1, 1, 1, 1)
		BLEND_SRC_COLOR,	// color(src.r, src.g, src.b, src.a)
		BLEND_INVS_SRC_COLOR,	// color(1 - src.r, 1 - src.g, 1 - src.b, 1 - src.a)
		BLEND_SRC_ALPHA,		// color(src.a, src.a, src.a src.a)
		BLEND_INVS_SRC_ALPHA,	// color(1 - src.a, 1 - src.a, 1 - src.a, 1 - src.a)
		BLEND_DST_ALPHA,		// color(dst.a, dst.a, dst.a, dst.a)
		BLEND_INV_DST_ALPHA,	// color(1 - dst.a, 1 - dst.a, 1 - dst.a, 1 - dst.a)
		BLEND_DST_COLOR,		// color(dst.r, dst.g, dst.b, dst.a)
		BLEND_INV_DST_COLOR,	// color(1 - dst.r, 1 - dst.g, 1 - dst.b, 1 - dst.a)
		BLEND_SRC_ALPHA_SAT,	// ?
		BLEND_CONSTANT,			// color(const.r, const.g, const.b, const.a)
		BLEND_INV_CONSTANT,		// color(1 - const.r, 1 - const.g, 1 - const.b, 1 - const.a)
	};

	// Depth��Ϣ
	struct DepthStateInfo{
		bool enabled;
		bool write_enabled;
		CompareFunc func;
	};

	// Stencil��Ϣ
	struct StencilOpInfo {
		StencilOperation s_fail;	// glStencilOp(
		StencilOperation z_pass;
		StencilOperation z_fail;
	};

	struct StencilStateInfo {
		bool enabled;

		CompareFunc func;	// glStencilFunc(func, ref, mask)
		unsigned int ref;
		unsigned int mask;

		struct StencilOpInfoSeparate {
			StencilOpInfo front;
			StencilOpInfo back;
		};
		bool separate;		// �Ƿ�ֿ�����
		union OpInfo
		{
			StencilOpInfo info;	// glStencilOp
			StencilOpInfoSeparate info_separate; // glStencilOpSeparate
		} op_info;
		
	};


	// Rasterize��Ϣ
	struct RasterizeStateInfo {
		FillMode fill_mode;
		CullMode cull_mode;
		bool front_ccw;
		bool scissor_test_enabled;	// �ü������Ƿ��
	};


	// Blend��Ϣ
	struct BlendStateInfo {
		bool enabled;
		BlendOperation blend_op;
		BlendFactor src_factor;
		BlendFactor dst_factor;
		
	};

	// RenderState
	struct RenderState {
		DepthStateInfo depth;
		StencilStateInfo stencil;
		RasterizeStateInfo raster;
		BlendStateInfo blend;
	};

	// shader types
	enum ShaderType {
		VertexShader,
		GeometryShader,
		FragmentShader,
	};


}
}

#endif
