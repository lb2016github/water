#include "transform_component.h"
#include "world/gameobjects/game_object.h"
#include "component_const.h"
#include "boost/algorithm/string.hpp"
#include "world/gameobjects/space_object.h"

namespace water {
	namespace world
	{
		REGISTER_COMPONENT(TransformComponent, GameObject);

		TransformComponent::TransformComponent(GameObject * space_object): BaseComponent(space_object)
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
			return math3d::get_transform_matrix(position, rotation, scale);
		}
		void TransformComponent::set_position(math3d::Vector3 pos)
		{
			position = pos;
		}
		void TransformComponent::set_position(std::string pos_str)
		{
			position = string_to_vector(pos_str);
		}
		void TransformComponent::set_scale(math3d::Vector3 p_scale)
		{
			scale = p_scale;
		}
		void TransformComponent::set_scale(std::string scale_str)
		{
			scale = string_to_vector(scale_str);
		}
		void TransformComponent::set_rotation(math3d::Vector3 p_rotation)
		{
			rotation = p_rotation;
		}
		void TransformComponent::set_rotation(std::string rot_str)
		{
			rotation = string_to_vector(rot_str);
		}
		inline math3d::Vector3 TransformComponent::string_to_vector(std::string str)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			assert(sub_values.size() == 3);
			return math3d::Vector3(atof(sub_values[0].c_str()), atof(sub_values[1].c_str()), atof(sub_values[2].c_str()));
		}
	}
}