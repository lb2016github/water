#ifndef WATER_RENDER_STATE_INFO_H
#define WATER_RENDER_STATE_INFO_H

namespace water {
namespace render {
	enum StencilOperation {
		STENCILOP_KEEP, ///< Do not update the entry in the stencil buffer. This is the default value. 
		STENCILOP_ZERO, ///< Set the stencil-buffer entry to 0. 
		STENCILOP_REPLACE, ///< Replace the stencil-buffer entry with a reference value.
		STENCILOP_INCR, ///< Increment the stencil-buffer entry, clamping to the maximum value.
		STENCILOP_DECR, ///< Decrement the stencil-buffer entry, clamping to zero.
		STENCILOP_INVERT, ///< Invert the bits in the stencil-buffer entry.
		STENCILOP_INCRWRAP,///< Increment the stencil-buffer entry, wrapping to zero if the new value exceeds the maximum value.
		STENCILOP_DECRWRAP, ///< Decrement the stencil-buffer entry, wrapping to the maximum value if the new value is less than zero. 
	};

	// 比较函数
	enum CompareFunc {
		CMP_NEVER,		// 永远失败
		CMP_LESS,		// 小于
		CMP_EQUAL,		// 等于
		CMP_LESS_EQUAL,	// 小于等于
		CMP_GREATER,	// 大于
		CMP_NOTEQUAL,	// 不等于
		CMP_GREATER_EQUAL,	// 大于等于
		CMP_ALWAYS		// 永远成功
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
		FILL_POINT,		// 点
		FILL_WIREFRAME,	// 线框
		FILL_SOLID,		// 实体
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

	// Depth信息
	struct DepthStateInfo{
		bool enabled;
		bool write_enabled;
		CompareFunc func;
	};

	// Stencil信息
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
		bool separate;		// 是否分开设置
		union OpInfo
		{
			StencilOpInfo info;	// glStencilOp
			StencilOpInfoSeparate info_separate; // glStencilOpSeparate
		} op_info;
		
	};


	// Rasterize信息
	struct RasterizeStateInfo {
		FillMode fill_mode;
		CullMode cull_mode;
		bool front_ccw;
		bool scissor_test_enabled;	// 裁剪测试是否打开
	};


	// Blend信息
	struct BlendStateInfo {
		bool enabled;
		BlendOperation blend_op;
		BlendFactor src_factor;
		BlendFactor dst_factor;
		
	};

	// RenderState
	struct RenderStateInfo {
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

	// draw mode
	enum MeshMode {
		POINTS,
		LINES,
		LINE_LOOP,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_TRIP,
		TRIANGLE_FAN,
		QUADS,
	};

	// texture types
	enum TextureType {
		TEXTURE_2D,
		TEXTURE_CUBE,
	};

	// render target attachments
	enum Attachment
	{
		ATTACHMENT_DEPTH,
		ATTACHMENT_STENCIL,
		ATTACHMENT_DEPTH_STENCIL,
		ATTACHMENT_COLOR_0,
		ATTACHMENT_COLOR_1,
		ATTACHMENT_COLOR_2,
		ATTACHMENT_COLOR_3,
		ATTACHMENT_COLOR_4,
	};

	enum TextureUnit
	{
		TEXTURE_UNIT_0 = 0,
		TEXTURE_UNIT_1,
		TEXTURE_UNIT_2,
		TEXTURE_UNIT_3,
		TEXTURE_UNIT_4,
		TEXTURE_UNIT_5,
	};

}
}

#endif
