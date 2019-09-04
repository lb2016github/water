#include "transform_component.h"
#include "world/gameobjects/game_object.h"
#include "component_const.h"

namespace water {
	namespace world
	{
		REGISTER_COMPONENT(COMP_TRANSFORMATION, TransformComponent, SpaceObject);

		TransformComponent::TransformComponent(SpaceObject * space_object): BaseComponent(space_object)
		{
		}

		TransformComponent& TransformComponent::operator=(const TransformComponent& trans_comp)
		{
			if (&trans_comp == this) {
				return *this;
			}
			BaseComponent::operator=(trans_comp);
			position = trans_comp.position;
			rotation = trans_comp.rotation;
			scale = trans_comp.scale;
			return *this;
		}

		math3d::Matrix TransformComponent::get_world_transformation()
		{
			SpaceObject* obj_ptr = (SpaceObject*)m_game_object;
			if (!obj_ptr || obj_ptr->get_parent() == NULL)
			{
				return get_transformation();
			}
			TransformComponent* parent_trans_comp = (TransformComponent*)obj_ptr->get_parent()->get_component(COMP_TRANSFORMATION);
			if (!parent_trans_comp)
			{
				return get_transformation();
			}
			return parent_trans_comp->get_world_transformation() * get_transformation();
		}

		math3d::Matrix TransformComponent::get_transformation()
		{
			return math3d::get_transform_matrix(position, rotation, scale);
		}
	}
}