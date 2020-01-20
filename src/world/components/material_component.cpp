#include "material_component.h"
#include "render/material.h"
#include "common/log.h"
#include "transform_component.h"
#include "scene_object_component.h"
#include "world/gameobjects/game_object.h"
#include "world/gameobjects/scene.h"
#include "world/gameobjects/world.h"
#include "shadowmap_component.h"
#include "mesh_component.h"
#include "world/animation/skeleton.h"
#include "animator_component.h"
#include "render/material_param.h"

namespace water
{
	namespace world
	{

		REGISTER_COMPONENT(MaterialComponent, GameObject)

		bool MaterialComponent::has_param(std::string name, unsigned int index)
		{
			auto ptr = m_material_ptr->getParamMap(index);
			if (!ptr) return false;
			return ptr->hasParam(name);
		}

		render::MaterialPtr MaterialComponent::get_material()
		{
			return m_material_ptr;
		}

		void MaterialComponent::update_material()
		{
			update_material(m_game_object, m_material_ptr);
		}

		void MaterialComponent::update_material(GameObject* game_object, render::MaterialPtr mat_ptr)
		{
			if (mat_ptr)
			{
				auto num = mat_ptr->getParamMapCount();
				for (unsigned int i = 0; i < num; ++i)
				{
					auto param_map = mat_ptr->getParamMap(i);
					if (!param_map) continue;
					for (auto iter = param_map->m_semanticMap.begin(); iter != param_map->m_semanticMap.end(); ++iter)
					{
						// update semantic
						update_semantic_param(game_object, param_map, iter->first, iter->second);
					}
				}
			}
		}

		void MaterialComponent::update_semantic_param(GameObject* game_object, render::MaterialParamMapPtr param_map, std::string name, render::SemanticType semantic)
		{
			auto scene_ptr = World::get_instance()->get_cur_scene();
			if (scene_ptr == nullptr) return;
			if (semantic == water::render::SemanticWVP)
			{
				auto trans_comp = GET_COMPONENT(game_object, TransformComponent);
				if (trans_comp == nullptr) return;
				auto world_trans = trans_comp->get_world_transformation();
				auto cam_ptr = scene_ptr->get_active_camera();
				if (cam_ptr == nullptr) return;
				auto view = cam_ptr->get_view_matrix();
				auto proj = cam_ptr->get_projection_matrix();
				auto wvp = proj * view * world_trans;
				param_map->setParam(name, wvp);
			}
			else if (semantic == water::render::SemanticVP)
			{
				auto cam_ptr = scene_ptr->get_active_camera();
				if (cam_ptr == nullptr) return;
				auto view = cam_ptr->get_view_matrix();
				auto proj = cam_ptr->get_projection_matrix();
				auto vp = proj * view;
				param_map->setParam(name, vp);
			}
			else if (semantic == water::render::SemanticWorld)
			{
				auto trans_comp = GET_COMPONENT(game_object, TransformComponent);
				if (trans_comp == nullptr) return;
				auto world_trans = trans_comp->get_world_transformation();
				param_map->setParam(name, world_trans);
			}
			else if (semantic == water::render::SemanticCameraPosition)
			{
				auto cam_ptr = scene_ptr->get_active_camera();
				if (cam_ptr == nullptr) return;
				auto cam_trans = GET_COMPONENT(cam_ptr, TransformComponent);
				auto cam_pos = cam_trans->position;
				param_map->setParam(name, cam_pos);

			}
			else if (semantic == water::render::SemanticLight)
			{
				param_map->setParam(name, render::StructParam::getStructParam(scene_ptr->get_light_config(), name));
			}
			else if (semantic == water::render::SemanticShadowMapVP)
			{
				auto shadow_map_comp = GET_COMPONENT(scene_ptr, ShadowMapComponent);
				param_map->setParam(name, shadow_map_comp->get_shadow_vp());
			}
			else if (semantic == water::render::SemanticShadowMapTexture)
			{
				auto shadow_map_comp = GET_COMPONENT(scene_ptr, ShadowMapComponent);
				param_map->setParam(name, shadow_map_comp->get_shadow_map());
			}
			else if (semantic == water::render::SemanticEnvMap)
			{
				auto env_map = scene_ptr->get_env_map();
				if (env_map)
				{
					param_map->setParam(name, env_map);
				}
			}
			else if (semantic == water::render::SemanticSkinMatrix)
			{
				auto animComp = GET_COMPONENT(game_object, AnimatorComponent);
				if (animComp)
				{
					auto skePose = animComp->getCurPose();
					// todo
				}
			}
		}


		MaterialComponent::MaterialComponent(GameObject * game_object): BaseComponent(game_object)
		{
			m_material_ptr = std::make_shared<render::Material>();
		}
		MaterialComponent & MaterialComponent::operator=(const MaterialComponent & comp)
		{
			if (this == &comp) return *this;
			BaseComponent::operator=(comp);
			m_material_ptr = comp.m_material_ptr;
			return *this;
		}
		MaterialComponent::~MaterialComponent()
		{
			m_material_ptr = nullptr;
		}
		void MaterialComponent::set_material(render::MaterialPtr material)
		{
			m_material_ptr = material;
		}
	}
}

