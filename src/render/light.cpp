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
					direction.normalize();
				}
				else
				{
					log_error("[LIGHT]DirectionLight unkown attribute name: %s \n%s", attr.name(), __FUNCSIG__);
				}
			}
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
		void SpotLight::init_from_xml(pugi::xml_node node)
		{
			PointLight::init_from_xml(node);
			for each (auto attr in node.attributes())
			{
				if (strcmp(attr.name(), "direction") == 0)
				{
					load_vec3_from_str(attr.as_string(), direction);
					direction.normalize();
				}
				else if (strcmp(attr.name(), "cutoff") == 0)
				{
					cutoff = attr.as_float();
				}
			}
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
	}
}
