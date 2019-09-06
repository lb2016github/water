#include "scene.h"
#include "world/components/render_component.h"
#include "filesystem/xml_file.h"
#include "common/log.h"
#include "model.h"
#include "world/components/transform_component.h"
#include "world/components/scene_object_component.h"

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
		void Scene::render(const render::DrawCommand & draw_cmd)
		{
			auto render_comp = GET_COMPONENT(this, RenderComponent);
			render_comp->render(draw_cmd);
		}
		void Scene::load_from_file(std::string filepath)
		{
			filesystem::XMLFile xml_file;
			xml_file.load(filepath.c_str());
			if (xml_file.m_loaded != true)
			{
				log_error("[MODEL]Fail to load file %s\n", filepath.c_str());
				return;
			}
			auto root_node = xml_file.get_root_node();
			for each (auto child in root_node.children())
			{
				// load model
				if (strcmp(child.name(), "Model") == 0)
				{
					std::string model_path = child.attribute("path").as_string();
					auto model = Model();
					model.load_from_file(model_path);
					// set pos rot scale
					auto scale = child.attribute("scale").as_string();
					if (scale) GET_COMPONENT(&model, TransformComponent)->set_scale(scale);
					auto rotation = child.attribute("scale").as_string();
					if (rotation) GET_COMPONENT(&model, TransformComponent)->set_rotation(rotation);
					auto position = child.attribute("position").as_string();
					if (position) GET_COMPONENT(&model, TransformComponent)->set_position(position);
					// add to scene
					model.add_component(SceneObjectComponent::tag);
					GET_COMPONENT(&model, SceneObjectComponent)->on_add_to_scene(std::dynamic_pointer_cast<Scene>(shared_from_this()));
				}
				// load camera
				if (strcmp(child.name(), "Camera") == 0)
				{
					auto camera = Camera();
					for (auto iter = child.attributes_begin(); iter != child.attributes_end(); ++iter)
					{
						if (strcmp(iter->name(), "fovy") == 0)
						{
							camera.fovy = iter->as_float();
						}
						else if (strcmp(iter->name(), "znear") == 0)
						{
							camera.z_near = iter->as_float();
						}
						else if (strcmp(iter->name(), "zfar") == 0)
						{
							camera.z_far = iter->as_float();
						}
						else if (strcmp(iter->name(), "position") == 0)
						{
							GET_COMPONENT(&camera, TransformComponent)->set_position(iter->as_string());
						}
						else if (strcmp(iter->name(), "rotation") == 0)
						{
							GET_COMPONENT(&camera, TransformComponent)->set_rotation(iter->as_string());
						}
						else
						{
							log_error("[Scene]Load camera attribute failed with name %s", iter->name());
						}
					}
				}
			}

		}

		std::set<ComponentTag> Scene::get_comp_tags()
		{
			auto rst = SpaceObject::get_comp_tags();
			rst.insert(RenderComponent::tag);
			return rst;
		}
	}
}
