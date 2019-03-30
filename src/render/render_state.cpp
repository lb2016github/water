#include "render/render_state.h"
#include "glad/glad.h"
#include "common/log.h"

namespace water {
	namespace render {

#define GL_CHECK_ERROR{\
		GLenum e = glGetError();\
		if (e != 0){\
			log_error("GL Error 0x04x in %s at line %i in %s", \
				e, __FUNCSIG__, __LINE__, __FILE__);\
		}\
		}

		void RenderStateOpenGL::apply_depth_state(DepthStateInfo* info /*= nullptr*/)
		{
			if (!info->enabled)
			{
				glDisable(GL_DEPTH_TEST);
				GL_CHECK_ERROR
				return;
			}
			glEnable(GL_DEPTH_TEST);
			glDepthMask(info->write_enabled ? true : false);
			glDepthFunc(get_gl_cmp_func(info->func));
			GL_CHECK_ERROR
		}

		void RenderStateOpenGL::apply_stencil_state(StencilStateInfo* info /*= nullptr*/)
		{
			if (!info->enabled)
			{
				glDisable(GL_STENCIL_TEST);
				GL_CHECK_ERROR
				return;
			}
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(get_gl_cmp_func(info->func), info->ref, info->mask);
			GL_CHECK_ERROR
			if (info->separate)
			{
				StencilOpInfo* front = &(info->op_info.info_separate.front);
				glStencilOpSeparate(GL_FRONT, front->s_fail, front->z_fail, front->z_pass);
				GL_CHECK_ERROR
				front = &(info->op_info.info_separate.back);
				glStencilOpSeparate(GL_BACK, front->s_fail, front->z_fail, front->z_pass);
				GL_CHECK_ERROR
			}
			else {
				StencilOpInfo* single_info = &(info->op_info.info);
				glStencilOpSeparate(GL_FRONT, single_info->s_fail, single_info->z_fail, single_info->z_pass);
				GL_CHECK_ERROR
			}
		}

		void RenderStateOpenGL::apply_rasterize_state(RasterizeStateInfo* info /*= nullptr*/)
		{
			if (info->cull_mode == CullMode::CULL_NONE)
			{
				glDisable(GL_CULL_FACE);
				GL_CHECK_ERROR;
			}
			else {
				glEnable(GL_CULL_FACE);
				GLenum cull_mode = info->cull_mode == CullMode::CULL_FRONT ? GL_FRONT : GL_BACK;
				glCullFace(cull_mode);
				glFrontFace(info->front_ccw ? GL_CCW : GL_CW);
				GL_CHECK_ERROR
			}
		}

		void RenderStateOpenGL::apply_blend_state(BlendStateInfo* info /*= nullptr*/)
		{
			if (!info->enabled) {
				glDisable(GL_BLEND);
				GL_CHECK_ERROR;
				return;
			}
			glEnable(GL_BLEND);
			GL_CHECK_ERROR;
			glBlendEquation(get_gl_blend_op(info->blend_op));
			GL_CHECK_ERROR;
			glBlendFunc(get_gl_blend_factor(info->src_factor), get_gl_blend_factor(info->dst_factor));
			GL_CHECK_ERROR;
		}

		////////////////////////////// LOCAL FUNCTION //////////////////////
		GLenum get_gl_cmp_func(CompareFunc func) {
			switch (func)
			{
			case water::render::CMP_NEVER:
				return GL_NEVER;
				break;
			case water::render::CMP_LESS:
				return GL_LESS;
				break;
			case water::render::CMP_EQUAL:
				return GL_EQUAL;
				break;
			case water::render::CMP_LESS_EQUAL:
				return GL_LEQUAL;
				break;
			case water::render::CMP_GREATER:
				return GL_GREATER;
				break;
			case water::render::CMP_NOTEQUAL:
				return GL_NOTEQUAL;
				break;
			case water::render::CMP_GREATER_EQUAL:
				return GL_GEQUAL;
				break;
			case water::render::CMP_ALWAYS:
				return GL_ALWAYS;
				break;
			default:
				return GL_ALWAYS;
				break;
			}
		}

		GLenum get_gl_blend_op(BlendOperation op) {
			switch (op)
			{
			case water::render::BLENDOP_ADD:
				return GL_FUNC_ADD;
				break;
			case water::render::BLENDOP_SUBTRACT:
				return GL_FUNC_SUBTRACT;
				break;
			case water::render::BLENDOP_REV_SUBTRACT:
				return GL_FUNC_REVERSE_SUBTRACT;
				break;
			case water::render::BLENDOP_MIN:
				log_warn("Blend min is not supported");
				break;
			case water::render::BLENDOP_MAX:
				log_warn("Blend max is not supported");
				break;
			default:
				break;
			}
		}

		GLenum get_gl_blend_factor(BlendFactor factor) {
			switch (factor)
			{
			case water::render::BLEND_ZERO:
				return GL_ZERO;
				break;
			case water::render::BLEND_ONE:
				return GL_ONE;
				break;
			case water::render::BLEND_SRC_COLOR:
				return GL_SRC_COLOR;
				break;
			case water::render::BLEND_INVS_SRC_COLOR:
				return GL_ONE_MINUS_SRC_COLOR;
				break;
			case water::render::BLEND_SRC_ALPHA:
				return GL_SRC_ALPHA;
				break;
			case water::render::BLEND_INVS_SRC_ALPHA:
				return GL_ONE_MINUS_SRC_ALPHA;
				break;
			case water::render::BLEND_DST_ALPHA:
				return GL_DST_ALPHA;
				break;
			case water::render::BLEND_INV_DST_ALPHA:
				return GL_ONE_MINUS_DST_ALPHA;
				break;
			case water::render::BLEND_DST_COLOR:
				return GL_DST_COLOR;
				break;
			case water::render::BLEND_INV_DST_COLOR:
				return GL_ONE_MINUS_DST_COLOR;
				break;
			case water::render::BLEND_SRC_ALPHA_SAT:
				return GL_SRC_ALPHA_SATURATE;
				break;
			case water::render::BLEND_CONSTANT:
				return GL_CONSTANT_COLOR;
				break;
			case water::render::BLEND_INV_CONSTANT:
				return GL_ONE_MINUS_CONSTANT_COLOR;
				break;
			default:
				log_error("Unkown blend factor %d", factor);
				break;
			}
		}
	}
}