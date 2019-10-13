#include "transform_component.h"
#include "world/gameobjects/game_object.h"
#include "component_const.h"
#include "world/gameobjects/space_object.h"
#include "math3d/math3d_common.h"

namespace water {
	namespace world
	{
		REGISTER_COMPONENT(TransformComponent, SpaceObject);

		TransformComponent::TransformComponent(SpaceObject * space_object): BaseComponent(space_object)
		{
			rotation = math3d::identity<math3d::Matrix>();
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
			SpaceObject* obj_ptr = dynamic_cast<SpaceObject*>(m_game_object);
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
			return math3d::get_translate_matrix(position) * rotation * math3d::get_scale_matrix(scale);
		}
		void TransformComponent::set_position(math3d::Vector3 pos)
		{
			position = pos;
		}
		void TransformComponent::set_position(std::string pos_str)
		{
			position = math3d::string_to_vector(pos_str);
		}
		void TransformComponent::set_scale(math3d::Vector3 p_scale)
		{
			scale = p_scale;
		}
		void TransformComponent::set_scale(std::string scale_str)
		{
			scale = math3d::string_to_vector(scale_str);
		}
		void TransformComponent::set_rotation(math3d::Vector3 p_rotation)
		{
			rotation = math3d::euler_angle_xyz(p_rotation);
		}
		void TransformComponent::set_rotation(std::string rot_str)
		{
			auto rot_euler = math3d::string_to_vector(rot_str);
			set_rotation(rot_euler);
		}
	}
}