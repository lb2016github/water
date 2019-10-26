#include "light.h"
#include <sstream>
#include <algorithm>
#include "boost/algorithm/string.hpp"
#include "common/log.h"

namespace water
{
	namespace render
	{
		template<typename key, typename value>
		void copy_map(const std::map<key, value>& src, std::map<key, value>& dst)
		{
			for (auto iter = src.begin(); iter != src.end(); ++iter)
			{
				dst[iter->first] = iter->second;
			}
		}

		void load_vec3_from_str(const std::string& str, math3d::Vector3& vec3)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			assert(sub_values.size() >= 3);
			vec3.x = atof(sub_values[0].c_str());
			vec3.y = atof(sub_values[1].c_str());
			vec3.z = atof(sub_values[2].c_str());
		}

		void BaseLight::init_from_xml(pugi::xml_node node)
		{
			for each (auto attr in node.attributes())
			{
				if (strcmp(attr.name(), "color") == 0)
				{
					load_vec3_from_str(attr.as_string(), color);
				}
				else if (strcmp(attr.name(), "ambiance_intensity") == 0)
				{
					ambiance_intensity = attr.as_float();
				}
				else if (strcmp(attr.name(), "diffuse_intensity") == 0)
				{
					diffuse_intensity = attr.as_float();
				}
				else
				{
					log_error("[LIGHT]BaseLight unkown attribute name: %s \n%s", attr.name(), __FUNCSIG__);
				}
			}
		}
		LightParamMap BaseLight::get_light_param_map(std::string base_name) const
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
		void DirectionLight::init_from_xml(pugi::xml_node node)
		{
			for each (auto child in node.children())
			{
				if (strcmp(child.name(), "BaseLight") == 0)
				{
					BaseLight::init_from_xml(child);
				}
				else
				{
					log_error("[LIGHT]DirectionLight unkown node name: %s \n%s", child.name(), __FUNCSIG__);
				}
			}
			for each (auto attr in node.attributes())
			{
				if (strcmp(attr.name(), "direction") == 0)
				{
					load_vec3_from_str(attr.as_string(), direction);
					direction = math3d::normalize(direction);
				}
				else
				{
					log_error("[LIGHT]DirectionLight unkown attribute name: %s \n%s", attr.name(), __FUNCSIG__);
				}
			}
		}
		LightParamMap DirectionLight::get_light_param_map(std::string base_name) const
		{
			std::string base_light_name = base_name + ".base_light";
			auto param = BaseLight::get_light_param_map(base_light_name);
			ParamValue p_direction;
			p_direction.vec3 = direction;
			param.value_map[base_name + ".direction"] = p_direction;
			param.type_map[base_name + ".direction"] = TypeVector3;
			return param;
		}
		void PointLight::init_from_xml(pugi::xml_node node)
		{
			for each (auto child in node.children())
			{
				if (strcmp(child.name(), "BaseLight") == 0)
				{
					BaseLight::init_from_xml(child);
				}
				else if (strcmp(child.name(), "Atten") == 0)
				{
					for each (auto attr in child.attributes())
					{
						if (strcmp(attr.name(), "constant") == 0)
						{
							atten.constant = attr.as_float();
						}
						else if (strcmp(attr.name(), "exp") == 0)
						{
							atten.exp = attr.as_float();
						}
						else if (strcmp(attr.name(), "linear") == 0)
						{
							atten.linear = attr.as_float();
						}
						else
						{
							log_error("[LIGHT]PointLight::Atten unkown attribute name: %s", attr.name());
						}
					}
				}
				else
				{
					log_error("[LIGHT]PointLight unkown node name: %s", child.name());
				}
			}
			for each (auto attr in node.attributes())
			{
				if (strcmp(attr.name(), "position") == 0)
				{
					load_vec3_from_str(attr.as_string(), position);
				}
			}
		}
		LightParamMap PointLight::get_light_param_map(std::string base_name) const
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
		void SpotLight::init_from_xml(pugi::xml_node node)
		{
			PointLight::init_from_xml(node);
			for each (auto attr in node.attributes())
			{
				if (strcmp(attr.name(), "direction") == 0)
				{
					load_vec3_from_str(attr.as_string(), direction);
					direction = math3d::normalize(direction);
				}
				else if (strcmp(attr.name(), "cutoff") == 0)
				{
					cutoff = attr.as_float();
				}
			}
		}
		LightParamMap SpotLight::get_light_param_map(std::string base_name) const
		{
			auto param = PointLight::get_light_param_map(base_name);
			ParamValue p_direction, p_cutoff;
			p_direction.vec3 = direction;
			p_cutoff.float_1 = cutoff;
			param.value_map[base_name + ".direction"] = p_direction;
			param.value_map[base_name + ".cutoff"] = p_cutoff;
			param.type_map[base_name + ".direction"] = TypeVector3;
			param.type_map[base_name + ".cutoff"] = TypeFloat;
			return param;

		}
		void LightConfig::init_from_xml(pugi::xml_node node)
		{
			for each (auto child in node.children())
			{
				if (strcmp(child.name(), "DirectionLight") == 0)
				{
					dir_light.init_from_xml(child);
				}
				else if (strcmp(child.name(), "PointLight") == 0)
				{
					PointLight pt;
					pt.init_from_xml(child);
					point_lights.push_back(pt);
				}
				else if (strcmp(child.name(), "SpotLight") == 0)
				{
					SpotLight sl;
					sl.init_from_xml(child);
					spot_lights.push_back(sl);
				}
				else
				{
					log_error("[LIGHT]Unkown name %s", child.name());
				}
			}

		}
		LightParamMap LightConfig::get_light_param_map(std::string base_name) const
		{
			LightParamMap param;
			// dir light
			std::string tmp_base_name = base_name + ".dir_light";
			auto tmp_param = dir_light.get_light_param_map(tmp_base_name);
			copy_map<std::string, ParamValue>(tmp_param.value_map, param.value_map);
			copy_map<std::string, ParamValueType>(tmp_param.type_map, param.type_map);

			int index = 0;
			for (auto iter = point_lights.begin(); iter != point_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << base_name << ".point_lights" << "[" << index << "]";
				std::string tmp_base_name = ss.str();
				auto tmp_param = iter->get_light_param_map(tmp_base_name);
				copy_map<std::string, ParamValue>(tmp_param.value_map, param.value_map);
				copy_map<std::string, ParamValueType>(tmp_param.type_map, param.type_map);
			}
			index = 0;
			for (auto iter = spot_lights.begin(); iter != spot_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << base_name << ".spot_lights" << "[" << index << "]";
				std::string tmp_base_name = ss.str();
				auto tmp_param = iter->get_light_param_map(tmp_base_name);
				copy_map<std::string, ParamValue>(tmp_param.value_map, param.value_map);
				copy_map<std::string, ParamValueType>(tmp_param.type_map, param.type_map);
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
