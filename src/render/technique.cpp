#include "technique.h"
#include "render/technique_loader_config.h"
#include "filesystem\xml_file.h"
#include "common\log.h"
#include <algorithm>
#include <sstream>

namespace water
{
	namespace render
	{
		void load_render_state(RenderState& render_state, pugi::xml_node& node);
		void load_blend_info(BlendStateInfo& blend, pugi::xml_node& node);
		void load_depth_info(DepthStateInfo& depth, pugi::xml_node& node);
		void load_stencil_info(StencilStateInfo& stencil, pugi::xml_node node);
		void load_rasterize_info(RasterizeStateInfo& raster, pugi::xml_node& node);
		int hex_binary_string_to_int(std::string str);

		void Technique::load(const char * file_path)
		{
			filesystem::XMLFile xml_file;
			xml_file.load(file_path);
			if (!xml_file.m_loaded) {
				log_error("[Render]Fail to load file: %s", file_path);
				return;
			}
			m_filepath = file_path;
			pugi::xml_node root = xml_file.get_root_node();
			pugi::xml_node technique = root.child("Technique");
			for (pugi::xml_node node_render_pass = technique.child("RenderPass"); node_render_pass; node_render_pass = node_render_pass.next_sibling("RenderPass"))
			{
				RenderPass render_pass;
				// init index
				render_pass.index = node_render_pass.attribute("index").as_int();
				// init render state
				load_render_state(render_pass.render_state, node_render_pass.child("RenderState"));
				// init program
				pugi::xml_node program_node = node_render_pass.child("Program");
				pugi::xml_attribute tmp_attr;
				tmp_attr = program_node.find_attribute("vertex_shader");
				if(tmp_attr)
				{
					render_pass.shaders[VertexShader] = tmp_attr.value();
				}
				tmp_attr = program_node.find_attribute("geometry_shader");
				if (tmp_attr)
				{
					render_pass.shaders[GeometryShader] = tmp_attr.value();
				}

				tmp_attr = program_node.find_attribute("fragment_shader");
				if (tmp_attr)
				{
					render_pass.shaders[FragmentShader] = tmp_attr.value();
				}
				m_render_pass_queue.push_back(render_pass);	// will copy the object?
			}
		}

		///////////////////////// define loaders ////////////////////////////////

		void load_render_state(RenderState& render_state, pugi::xml_node& node)
		{
			load_blend_info(render_state.blend, node.child("BlendStateInfo"));
			load_depth_info(render_state.depth, node.child("DepthStateInfo"));
			load_stencil_info(render_state.stencil, node.child("StencilStateInfo"));
			load_rasterize_info(render_state.raster, node.child("RasterizeStateInfo"));
		}

		/*load blend info*/
		void load_blend_info(BlendStateInfo& blend, pugi::xml_node& node)
		{
			blend.enabled = node.attribute("enabled").as_bool();
			if (blend.enabled)
			{
				blend.blend_op = CONFIG_BlendOperation[node.child("BlendOperation").child_value()];
				blend.src_factor = CONFIG_BlendFactor[node.child("SrcFactor").child_value()];
				blend.dst_factor = CONFIG_BlendFactor[node.child("DstFactor").child_value()];
			}
		}

		/*Load depth info*/
		void load_depth_info(DepthStateInfo& depth, pugi::xml_node& node)
		{
			depth.enabled = node.attribute("enabled").as_bool();
			depth.write_enabled = node.attribute("write_enabled").as_bool();
			if (depth.enabled)
			{
				depth.func = CONFIG_CompareFunc[node.child("CompareFunc").child_value()];
			}
		}

		/*Load stencil info*/
		void load_stencil_info(StencilStateInfo& stencil, pugi::xml_node node)
		{
			stencil.enabled = node.attribute("enabled").as_bool();
			if (stencil.enabled)
			{
				stencil.func = CONFIG_CompareFunc[node.child("CompareFunc").child_value()];
				stencil.ref = hex_binary_string_to_int(node.child("Ref").child_value());
				stencil.mask = hex_binary_string_to_int(node.child("Mask").child_value());
				pugi::xml_node op_node = node.child("StencilOperation");
				if (op_node)
				{
					stencil.separate = true;
					stencil.op_info.info.s_fail = CONFIG_StencilOperation[op_node.child("SFail").child_value()];
					stencil.op_info.info.z_fail = CONFIG_StencilOperation[op_node.child("ZFail").child_value()];
					stencil.op_info.info.z_pass = CONFIG_StencilOperation[op_node.child("ZPass").child_value()];
				}
				else
				{
					stencil.separate = false;
					op_node = node.child("StencilOperationSep");
					if (!op_node)
					{
						log_error("StencilOperationSep is needed, but not found");
						return;
					}
					// front
					pugi::xml_node sub_node = op_node.child("Front");
					stencil.op_info.info_separate.front.s_fail = CONFIG_StencilOperation[sub_node.child("SFail").child_value()];
					stencil.op_info.info_separate.front.z_fail = CONFIG_StencilOperation[sub_node.child("ZFail").child_value()];
					stencil.op_info.info_separate.front.z_pass = CONFIG_StencilOperation[sub_node.child("ZPass").child_value()];
					// back
					sub_node = op_node.child("Front");
					stencil.op_info.info_separate.back.s_fail = CONFIG_StencilOperation[sub_node.child("SFail").child_value()];
					stencil.op_info.info_separate.back.z_fail = CONFIG_StencilOperation[sub_node.child("ZFail").child_value()];
					stencil.op_info.info_separate.back.z_pass = CONFIG_StencilOperation[sub_node.child("ZPass").child_value()];
				}
			}
		}

		/*Load rasterize info*/
		void load_rasterize_info(RasterizeStateInfo& raster, pugi::xml_node& node)
		{
			raster.cull_mode = CONFIG_CullMode[node.child("CullMode").child_value()];
			if (raster.cull_mode != CULL_NONE)
			{
				raster.front_ccw = node.attribute("front_ccw").as_bool();
			}
			raster.fill_mode = CONFIG_FillMode[node.child("FillMode").child_value()];
			raster.scissor_test_enabled = node.attribute("scissor_test_enabled").as_bool();
		}

		/*hexbinary string to int*/
		int hex_binary_string_to_int(std::string str)
		{
			std::stringstream ss;
			int n;
			ss << std::hex << str;
			ss >> n;
			return n;
		}

	}
}
