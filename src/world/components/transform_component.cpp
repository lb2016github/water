#include "transform_component.h"
#include "world/gameobjects/game_object.h"
#include "component_const.h"

namespace water {
	namespace world
	{
		ComponentTag TransformComponent::tag = COMP_TRANSFORMATION;
		Component* TransformComponent::create_component(GameObject* gameobject)
		{
			return new TransformComponent(gameobject);
		}
		ComponentInfo comp_info(TransformComponent::tag, TransformComponent::create_component);

		TransformComponent::TransformComponent(): Component(), transformation(1)
		{

		}

		TransformComponent::TransformComponent(GameObject* game_object): Component(game_object), transformation(1)
		{

		}

		TransformComponent::TransformComponent(const TransformComponent& trans_comp): Component(trans_comp)
		{
			transformation = trans_comp.transformation;
		}

		math3d::Matrix TransformComponent::get_world_transformation()
		{
			if (!m_game_object || m_game_object->m_parent == NULL)
			{
				return transformation;
			}
			TransformComponent* parent_trans_comp = (TransformComponent*)m_game_object->m_parent->get_component(COMP_TRANSFORMATION);
			if (!parent_trans_comp)
			{
				return transformation;
			}
			return parent_trans_comp->get_world_transformation() * transformation;
		}

		TransformComponent& TransformComponent::operator=(const TransformComponent& trans_comp)
		{
			if (&trans_comp == this) {
				return *this;
			}
			Component::operator=(trans_comp);
			transformation = trans_comp.transformation;
			return *this;
		}
	}
}