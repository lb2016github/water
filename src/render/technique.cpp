#include "render/technique.h"
#include "render/technique_common.h"
#include "render/render_program.h"
#include "render/render_task.h"
#include "render/render_object.h"
#include "filesystem\xml_file.h"
#include "common\log.h"
#include <algorithm>
#include <sstream>
#include "render/device.h"

namespace water
{
	namespace render
	{
		TechniqueManager* TechniqueManager::instance = nullptr;

		void load_render_state(RenderStateInfo& render_state, pugi::xml_node& node);
		void load_blend_info(BlendStateInfo& blend, pugi::xml_node& node);
		void load_depth_info(DepthStateInfo& depth, pugi::xml_node& node);
		void load_stencil_info(StencilStateInfo& stencil, pugi::xml_node node);
		void load_rasterize_info(RasterizeStateInfo& raster, pugi::xml_node& node);
		int hex_binary_string_to_int(std::string str);


		///////////////////////// define loaders ////////////////////////////////

		void load_render_state(RenderStateInfo& render_state, pugi::xml_node& node)
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

		TechniquePtr TechniqueManager::get_technique(std::string & file_path)
		{
			if (m_tech_map.find(file_path) != m_tech_map.end())
			{
				return m_tech_map[file_path];
			}

			// load technique
			if (do_load(file_path))
			{
				return m_tech_map[file_path];
			}

			return nullptr;
		}

		TechniqueManager* TechniqueManager::get_instance()
		{
			if (!instance)
			{
				instance = new TechniqueManager();
			}
			return instance;
		}

		bool TechniqueManager::do_load(std::string & file_path)
		{
			TechniquePtr tech = std::make_shared<Technique>();
			filesystem::XMLFile xml_file;
			xml_file.load(file_path.c_str());
			if (!xml_file.m_loaded) {
				log_error("[Render]Fail to load file: %s", file_path);
				return false;
			}
			tech->m_filepath = file_path;
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
				std::string vertex_shader = "", geom_shader = "", frag_shader = "";
				tmp_attr = program_node.attribute("vertex_shader");
				if(!tmp_attr.empty())
				{
					vertex_shader = tmp_attr.as_string();
				}
				tmp_attr = program_node.attribute("geometry_shader");
				if (!tmp_attr.empty())
				{
					geom_shader = tmp_attr.as_string();
				}

				tmp_attr = program_node.attribute("fragment_shader");
				if (!tmp_attr.empty())
				{
					frag_shader = tmp_attr.as_string();
				}
				render_pass.program = get_device()->get_program_manager()->load_program(vertex_shader, geom_shader, frag_shader);
				tech->m_render_pass_queue.push_back(render_pass);	// will copy the object?
				// load attribute param type
				ParamTypeMap attribute_map;
				for (pugi::xml_node attr_node = program_node.child("Attribute"); attr_node; attr_node = program_node.next_sibling("Attribute"))
				{
					std::string type = attr_node.attribute("type").as_string();
					std::map<std::string, ParamValueType>::iterator iter = CONFIG_param_type.find(type);
					if (iter == CONFIG_param_type.end())
					{
						log_error("Iegal param type %s", type);
						continue;
					}
					attribute_map[attr_node.attribute("name").as_string()] = iter->second;
				}
				render_pass.program->set_attribute_config(attribute_map);
				// load uniform param type
				ParamTypeMap uniform_map;
				for (pugi::xml_node attr_node = program_node.child("Uniform"); attr_node; attr_node = program_node.next_sibling("Uniform"))
				{
					std::string type = attr_node.attribute("type").as_string();
					std::map<std::string, ParamValueType>::iterator iter = CONFIG_param_type.find(type);
					if (iter == CONFIG_param_type.end())
					{
						log_error("Illegal param type %s", type);
						continue;
					}
					uniform_map[attr_node.attribute("name").as_string()] = iter->second;
				}
				render_pass.program->set_uniform_config(uniform_map);
			}
			m_tech_map[file_path] = tech;
			return true;
		}

		void Technique::render(IRenderable* render_obj)
		{
			render(render_obj->get_draw_command(), render_obj->get_material(), render_obj->get_mesh());
		}

		void Technique::render(const DrawCommand& draw_cmd, MaterialPtr mat_ptr, MeshDataPtr mesh_ptr)
		{
			RenderTaskPtr pre_task = nullptr;
			int cur_idx = 0;
			for (std::vector<RenderPass>::iterator iter = m_render_pass_queue.begin(); iter != m_render_pass_queue.end(); ++iter, ++cur_idx)
			{
				RenderTaskPtr cur_task = std::make_shared<RenderTask>(
					draw_cmd,
					mesh_ptr, iter->program, iter->render_state,
					*(mat_ptr->get_param_map(cur_idx)), pre_task
				);
				RenderTaskManager::get_instance()->add_task(cur_task);
				pre_task = cur_task;
			}
		}

}
}
