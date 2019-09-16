#ifndef WATER_LIGHT_H
#define WATER_LIGHT_H

#include "math3d/math3d.hpp"
#include "technique_common.h"
#include <vector>
#include <string>
#include "pugixml/pugixml.hpp"

#define COLOR_WHITE math3d::Vector3(1.0f, 1.0f, 1.0f)
#define COLOR_RED math3d::Vector3(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN math3d::Vector3(0.0f, 1.0f, 0.0f)
#define COLOR_CYAN math3d::Vector3(0.0f, 1.0f, 1.0f)
#define COLOR_BLUE math3d::Vector3(0.0f, 0.0f, 1.0f)

namespace water
{
	namespace render
	{
		struct LightParamMap {
			ParamTypeMap type_map;
			ParamValueMap value_map;
		};

		struct BaseLight
		{
			virtual void init_from_xml(pugi::xml_node node);
			virtual LightParamMap get_light_param_map(std::string base_name) const;
			math3d::Vector3 color = { 0, 0, 0 };
			float ambiance_intensity = { 0 };
			float diffuse_intensity = { 0 };
		};

		struct DirectionLight : BaseLight
		{
			virtual void init_from_xml(pugi::xml_node node);
			virtual LightParamMap get_light_param_map(std::string base_name) const;
			math3d::Vector3 direction = { 0, 0, 0 };
		};

		struct PointLight : BaseLight
		{
			virtual void init_from_xml(pugi::xml_node node);
			virtual LightParamMap get_light_param_map(std::string base_name) const;
			struct Atten
			{
				float constant = { 1 };
				float linear = { 0 };
				float exp = { 0 };
			};
			Atten atten;
			math3d::Vector3 position = { 0, 0, 0 };
		};

		struct SpotLight : PointLight
		{
			virtual void init_from_xml(pugi::xml_node node);
			virtual LightParamMap get_light_param_map(std::string base_name) const;
			math3d::Vector3 direction = { 0, 0, 0 };
			float cutoff = { 20 };	// 
		};

		struct LightConfig
		{
			virtual void init_from_xml(pugi::xml_node node);
			LightParamMap get_light_param_map(std::string base_name) const;
			DirectionLight dir_light;
			std::vector<PointLight> point_lights;
			std::vector<SpotLight> spot_lights;
		};

	}
}

#endif // !WATER_LIGHT_H
