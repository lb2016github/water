#include "scene.h"
#include "world/components/render_component.h"
#include "filesystem/xml_file.h"
#include "common/log.h"
#include "model.h"
#include "world/components/transform_component.h"
#include "world/components/scene_object_component.h"
#include "filesystem/filesystem.h"
#include "world/components/shadowmap_component.h"
#include "billboardlist.h"
#include "math3d/math3d_common.h"
#include "render/device.h"

namespace water
{
	namespace world
	{
		CameraPtr Scene::get_active_camera()
		{
			return m_cur_camera;
		}
		void Scene::set_active_camera(CameraPtr cam_ptr)
		{
			m_cur_camera = cam_ptr;
		}
		render::LightConfig Scene::get_light_config()
		{
			return m_light_cfg;
		}
		render::TexturePtr Scene::get_env_map()
		{
			return m_env;
		}
		void Scene::render()
		{
			if (enable_shadowmap)
			{
				auto shadow_map_comp = GET_COMPONENT(this, ShadowMapComponent);
				shadow_map_comp->render();
			}

			for each (auto bbl in m_billboards)
			{
				bbl->render();
			}

			auto render_comp = GET_COMPONENT(this, RenderComponent);
			render_comp->render();
		}
		void Scene::load_from_file(std::string filepath)
		{
			filesystem::XMLFile xml_file;
			xml_file.load(filepath);
			if (xml_file.m_loaded != true)
			{
				log_error("[MODEL]Fail to load file %s\n", filepath.c_str());
				return;
			}
			auto root_node = xml_file.get_root_node();
			root_node = root_node.first_child();
			for each (auto child in root_node.children())
			{
				// load model
				if (strcmp(child.name(), "Model") == 0)
				{
					std::string model_path = child.attribute("path").as_string();
					auto model = std::make_shared<Model>();
					model->load_from_file(model_path);
					// set pos rot scale
					auto scale = child.attribute("scale").as_string();
					if (scale) GET_COMPONENT(model, TransformComponent)->set_scale(scale);
					auto rotation = child.attribute("rotation").as_string();
					if (rotation) GET_COMPONENT(model, TransformComponent)->set_rotation(rotation);
					auto position = child.attribute("position").as_string();
					if (position) GET_COMPONENT(model, TransformComponent)->set_position(position);
					// add child
					auto shared_ptr = model->shared_from_this();
					add_child(shared_ptr);
					//// add to scene
					//model->add_component(SceneObjectComponent::tag);
					//GET_COMPONENT(model, SceneObjectComponent)->on_add_to_scene(std::dynamic_pointer_cast<Scene>(shared_from_this()));
				}
				// load camera
				else if (strcmp(child.name(), "Camera") == 0)
				{
					auto camera = std::make_shared<Camera>();
					add_child(camera);
					camera->update_fovy();
					for (auto iter = child.attributes_begin(); iter != child.attributes_end(); ++iter)
					{
						if (strcmp(iter->name(), "fovy") == 0)
						{
							camera->fovy = iter->as_float();
						}
						else if (strcmp(iter->name(), "znear") == 0)
						{
							camera->z_near = iter->as_float();
						}
						else if (strcmp(iter->name(), "zfar") == 0)
						{
							camera->z_far = iter->as_float();
						}
						else if (strcmp(iter->name(), "position") == 0)
						{
							GET_COMPONENT(camera, TransformComponent)->set_position(iter->as_string());
						}
						else if (strcmp(iter->name(), "rotation") == 0)
						{
							GET_COMPONENT(camera, TransformComponent)->set_rotation(iter->as_string());
						}
						else if (strcmp(iter->name(), "active") == 0)
						{
							if (iter->as_bool())
							{
								set_active_camera(camera);
							}
						}
						else
						{
							log_error("[Scene]Load camera attribute failed with name %s", iter->name());
						}
					}
				}
				// load env map
				else if (strcmp(child.name(), "EnvMap") == 0)
				{
					std::string path = child.attribute("Path").as_string();
					auto img = std::make_shared<filesystem::Image>(path);
					auto tex_data = std::make_shared<render::TextureData>();
					tex_data->images.emplace_back(img);
					tex_data->load();
					m_env = render::get_device()->create_texture(render::TEXTURE_2D);
					m_env->set_tex_data(tex_data);
				}
				// load light
				else if (strcmp(child.name(), "LightConfig") == 0)
				{
					m_light_cfg.init_from_xml(child);
				}
				// load shadow map
				else if (strcmp(child.name(), "ShadowMap") == 0)
				{
					enable_shadowmap = child.attribute("enable").as_bool();
					if (enable_shadowmap)
					{
						auto shadow_map_comp = dynamic_cast<ShadowMapComponent*>(get_component(ShadowMapComponent::tag, true));
						shadow_map_comp->init(child.attribute("material").as_string());
					}
				}
				// load billboard list
				else if (strcmp(child.name(), "BillboardList") == 0)
				{
					BillboardListPtr ptr = std::make_shared<BillboardList>();
					ptr->set_material(child.attribute("material").as_string());
					ptr->set_size(child.attribute("size").as_string());
					std::vector<math3d::Vector3> positions;
					for each(auto sub_child in child.children())
					{
						positions.push_back(math3d::string_to_vector(sub_child.text().as_string()));
					}
					ptr->set_positions(positions);
					m_billboards.push_back(ptr);
				}

			}

		}

		void Scene::on_frame()
		{
			if (m_cur_camera)
			{
				m_cur_camera->update();
			}
			render();
		}
	}
}
