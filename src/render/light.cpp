#include "light.h"
#include <sstream>
#include <algorithm>

namespace water
{
	namespace render
	{
		LightParamMap BaseLight::get_light_param_map(std::string base_name)
		{
			auto param =  LightParamMap();
			ParamValue p_color, p_ambiance, p_diffuse;
			p_color.vec3 = color;
			p_ambiance.float_1 = ambiance_intensity;
			p_diffuse.float_1 = diffuse_intensity;
			param.value_map = ParamValueMap
			{
				{base_name + ".color", p_color},
				{base_name + ".ambiance_intensity", p_ambiance},
				{base_name + ".diffuse_intensity", p_diffuse},
			};
			param.type_map = ParamTypeMap
			{
				{base_name + ".color", TypeVector3},
				{base_name + ".ambiance_intensity", TypeFloat},
				{base_name + ".diffuse_intensity", TypeFloat},
			};
			return param;
		}
		LightParamMap DirectionLight::get_light_param_map(std::string base_name)
		{
			std::string base_light_name = base_name + ".base_light";
			auto param = BaseLight::get_light_param_map(base_light_name);
			ParamValue p_direction;
			p_direction.vec3 = direction;
			param.value_map[base_name + ".direction"] = p_direction;
			param.type_map[base_name + ".direction"] = TypeVector3;
			return param;
		}
		LightParamMap PointLight::get_light_param_map(std::string base_name)
		{
			std::string base_light_name = base_name + ".base_light";
			auto param = BaseLight::get_light_param_map(base_light_name);
			ParamValue p_pos, p_constant, p_linear, p_exp;
			p_pos.vec3 = position;
			p_constant.float_1 = atten.constant;
			p_linear.float_1 = atten.linear;
			p_exp.float_1 = atten.exp;
			param.value_map[base_name + ".position"] = p_pos;
			param.value_map[base_name + ".atten.constant"] = p_constant;
			param.value_map[base_name + ".atten.linear"] = p_linear;
			param.value_map[base_name + ".atten.exp"] = p_exp;

			param.type_map[base_name + ".position"] = TypeVector3;
			param.type_map[base_name + ".atten.constant"] = TypeFloat;
			param.type_map[base_name + ".atten.linear"] = TypeFloat;
			param.type_map[base_name + ".atten.exp"] = TypeFloat;
			return param;
		}
		LightParamMap SpotLight::get_light_param_map(std::string base_name)
		{
			std::string base_light_name = base_name + ".base_light";
			auto param = BaseLight::get_light_param_map(base_light_name);
			ParamValue p_direction, p_cutoff;
			p_direction.vec3 = direction;
			p_cutoff.float_1 = cutoff;
			param.value_map[base_name + ".direction"] = p_direction;
			param.value_map[base_name + ".cutoff"] = p_cutoff;
			param.type_map[base_name + ".direction"] = TypeVector3;
			param.type_map[base_name + ".cutoff"] = TypeFloat;
			return param;

		}
		LightParamMap LightConfig::get_light_param_map(std::string base_name)
		{
			LightParamMap param;
			// dir light
			std::string tmp_base_name = base_name + ".dir_light";
			auto tmp_param = dir_light.get_light_param_map(tmp_base_name);
			std::move(tmp_param.value_map.begin(), tmp_param.value_map.end(), param.value_map.end());
			std::move(tmp_param.type_map.begin(), tmp_param.type_map.end(), param.type_map.end());

			int index = 0;
			for (auto iter = point_lights.begin(); iter != point_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << base_name << ".point_lights" << "[" << index << "]";
				std::string tmp_base_name = ss.str();
				auto tmp_param = iter->get_light_param_map(tmp_base_name);
				std::move(tmp_param.value_map.begin(), tmp_param.value_map.end(), param.value_map.end());
				std::move(tmp_param.type_map.begin(), tmp_param.type_map.end(), param.type_map.end());
			}
			index = 0;
			for (auto iter = spot_lights.begin(); iter != spot_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << base_name << ".spot_lights" << "[" << index << "]";
				std::string tmp_base_name = ss.str();
				auto tmp_param = iter->get_light_param_map(tmp_base_name);
				std::move(tmp_param.value_map.begin(), tmp_param.value_map.end(), param.value_map.end());
				std::move(tmp_param.type_map.begin(), tmp_param.type_map.end(), param.type_map.end());
			}
			ParamValue p_point_light_num, p_spot_light_num;
			p_point_light_num.float_1 = point_lights.size();
			p_spot_light_num.float_1 = spot_lights.size();
			param.value_map[base_name + ".point_light_num"] = p_point_light_num;
			param.type_map[base_name + ".point_light_num"] = TypeFloat;
			param.value_map[base_name + ".spot_light_num"] = p_spot_light_num;
			param.type_map[base_name + ".spot_light_num"] = TypeFloat;

			return param;
		}
	}
}
