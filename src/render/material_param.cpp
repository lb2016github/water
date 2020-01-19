#include "material_param.h"
#include "boost/algorithm/string.hpp"
#include "common/log.h"
#include <sstream>

namespace water
{
	namespace render
	{
		// load value from str
		void loadFromString(const std::string& str, int* value);
		void loadFromString(const std::string& str, float* value);
		void loadFromString(const std::string& str, math3d::Vector2* value);
		void loadFromString(const std::string& str, math3d::Vector3* value);
		void loadFromString(const std::string& str, math3d::Matrix* value);
		void loadFromString(const std::string& str, TexturePtr& value)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			auto texPtr = std::make_shared<TextureData>();
			unsigned int requireSize = 0;
			switch (sub_values.size())
			{
			case 2:
				texPtr->tex_type = TEXTURE_2D;
				requireSize = 2;
				break;
			case 6:
				texPtr->tex_type = TEXTURE_CUBE;
				requireSize = 6;
				break;
			default:
				log_error("[TEXTURE INIT]Ellegal images count(%d)", sub_values.size());
				return;
				break;
			}
			for(int i = 0; i < requireSize; ++i)
			{
				auto img_ptr = std::make_shared<filesystem::Image>();
				img_ptr->load(sub_values[i]);
				texPtr->images.push_back(img_ptr);
			}
			value = TextureManager::get_instance()->get_texture(texPtr);
		}

		MaterialParam::MaterialParam(UniformType type):
			m_type(type), m_data(nullptr)
		{
		}

		MaterialParam::MaterialParam(UniformType pType, const std::string& str):
			m_type(pType), m_data(nullptr)
		{
			assert(pType != UniformType::TypeStruct);
			switch (m_type)
			{
				case UniformType::TypeFloat:
					loadFromString(str, m_float);
					break;
				case UniformType::TypeInt:
					m_int = new int(0);
					loadFromString(str, m_int);
					break;
				case UniformType::TypeMatrix:
					loadFromString(str, m_mtx);
					break;
				case UniformType::TypeVector2:
					loadFromString(str, m_vec2);
					break;
				case UniformType::TypeVector3:
					loadFromString(str, m_vec3);
					break;
				case UniformType::TypeCubeMap:
				case UniformType::TypeSampler2D:
					loadFromString(str, m_tex);
					break;
				case UniformType::TypeMatrixArray:
					m_mtxArray = new std::vector<math3d::Matrix>();
					break;
				default:
					log_error("Illegal type: %d", m_type);
					break;
			}
		}
		MaterialParam::MaterialParam(const MaterialParam& param):
			m_type(param.m_type), m_data(nullptr)
		{
			_initData(param);
		}
		MaterialParam::MaterialParam(MaterialParam&& param):
			m_type(param.m_type), m_data(param.m_data)
		{
			param.m_data = nullptr;
		}
		MaterialParam::~MaterialParam()
		{
			_releaseData();
		}
		MaterialParam& MaterialParam::operator=(const MaterialParam& param)
		{
			if (this == &param) return *this;
			m_type = param.m_type;
			_releaseData();
			_initData(param);
		}
		MaterialParam& MaterialParam::operator=(MaterialParam&& param)
		{
			if (this == &param) return *this;
			m_type = param.m_type;
			_releaseData();
			m_data = param.m_data;
			param.m_data = nullptr;
			return *this;
		}
		void MaterialParam::_releaseData()
		{
			if (m_data)
			{
				switch (m_type)
				{
				case UniformType::TypeFloat :
					delete m_float;
					break;
				case UniformType::TypeInt:
					delete m_int;
					break;
				case UniformType::TypeMatrix:
					delete m_mtx;
					break;
				case UniformType::TypeVector2:
					delete m_vec2;
					break;
				case UniformType::TypeVector3:
					delete m_vec3;
					break;
				case UniformType::TypeCubeMap:
				case UniformType::TypeSampler2D:
					m_tex = nullptr;
					break;
				case UniformType::TypeMatrixArray:
					delete m_mtxArray;
					break;
				case UniformType::TypeStruct:
					delete m_struct;
				default:
					log_error("Unkown type: %d", m_type);
					break;
				}
			}
		}
		void MaterialParam::_initData(const MaterialParam& param)
		{
			if (param.m_data == nullptr)
			{
				m_data = param.m_data;
				return;
			}
			switch (param.m_type)
			{
			case UniformType::TypeFloat :
				m_float = new float(*param.m_float);
				break;
			case UniformType::TypeInt:
				m_int = new int(*param.m_int);
				break;
			case UniformType::TypeMatrix:
				m_mtx = new math3d::Matrix(*param.m_mtx);
				break;
			case UniformType::TypeVector2:
				m_vec2 = new math3d::Vector2(*param.m_vec2);
				break;
			case UniformType::TypeVector3:
				m_vec3 = new math3d::Vector3(*param.m_vec3);
				break;
			case UniformType::TypeCubeMap:
			case UniformType::TypeSampler2D:
				m_tex = param.m_tex;
				break;
			case UniformType::TypeMatrixArray:
				m_mtxArray = new MatrixArray();
				m_mtxArray->insert(m_mtxArray->begin(), param.m_mtxArray->begin(), param.m_mtxArray->end());
				break;
			case UniformType::TypeStruct:
				m_struct = new StructParam(*param.m_struct);
				break;
			default:
				log_error("Unkown type: %d", param.m_type);
				break;
			}
		}
		MaterialParamMap::MaterialParamMap()
		{
		}
		MaterialParamMap::MaterialParamMap(const MaterialParamMap& matParamMap):
			m_paramMap(matParamMap.m_paramMap), m_semanticMap(matParamMap.m_semanticMap)
		{

		}
		MaterialParamMap::MaterialParamMap(MaterialParamMap&& matParamMap):
			m_paramMap(std::move(matParamMap.m_paramMap)), m_semanticMap(std::move(matParamMap.m_semanticMap))
		{
		}
		void MaterialParamMap::unionMap(const MaterialParamMap& paramMap)
		{
			for (auto iter = paramMap.m_paramMap.begin(); iter != paramMap.m_paramMap.end(); ++iter)
			{
				if (m_paramMap.find(iter->first) == m_paramMap.end())
				{
					m_paramMap[iter->first] = iter->second;
				}
			}
		}
		bool MaterialParamMap::hasParam(const std::string& name)
		{
			for (auto iter = m_paramMap.begin(); iter != m_paramMap.end(); ++iter)
			{
				if(iter->first == name) return true;
				MaterialParam& param = iter->second;
				if (param.m_type == UniformType::TypeStruct)
				{
					if (param.m_struct && param.m_struct->hasParam(name)) return true;
				}
			}
			return false;
		}
		void MaterialParamMap::setParam(const std::string& name, const MaterialParam& pvalue)
		{
			m_paramMap[name] = pvalue;
		}
		void MaterialParamMap::setParam(const std::string& name, int value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeInt, value);
		}
		void MaterialParamMap::setParam(const std::string& name, float value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeFloat, value);
		}
		void MaterialParamMap::setParam(const std::string& name, const math3d::Matrix& value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeMatrix, value);
		}
		void MaterialParamMap::setParam(const std::string& name, const math3d::Vector3& value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeVector3, value);
		}
		void MaterialParamMap::setParam(const std::string& name, const math3d::Vector2& value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeVector2, value);
		}
		void MaterialParamMap::setParam(const std::string& name, const MaterialParam::MatrixArray& value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeMatrixArray, value);
		}
		void MaterialParamMap::setParam(const std::string& name, TexturePtr tex_ptr)
		{
			switch (tex_ptr->m_type)
			{
			case TEXTURE_2D:
				m_paramMap[name] = MaterialParam(UniformType::TypeSampler2D, tex_ptr);
				break;
			case TEXTURE_CUBE:
				m_paramMap[name] = MaterialParam(UniformType::TypeCubeMap, tex_ptr);
				break;
			}
		}
		void MaterialParamMap::setParam(const std::string& name, StructParam& value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeStruct, value);
		}
		const MaterialParam* MaterialParamMap::getParam(const std::string& name)
		{
			auto rst = m_paramMap.find(name);
			if (rst == m_paramMap.end()) return nullptr;
			return &(rst->second);
		}
		std::map<std::string, UniformType> MaterialParamMap::getUniformMap()
		{
			std::map<std::string, UniformType> result;
			for (auto iter = m_paramMap.begin(); iter != m_paramMap.end(); ++iter)
			{
				result[iter->first] = iter->second.m_type;
			}
			return result;
		}
		void MaterialParamMap::setRawParam(const std::string& name, const std::string& type, const std::string& raw_value, const std::string& semantic)
		{
			auto rst = CONFIG_uniform_type.find(type);
			// init parameters
			if (rst == CONFIG_uniform_type.end())
			{
				log_error("Type %s is unkown\n", type);
				return;
			}

			UniformType uType = rst->second;
			// init semantic
			auto semRst = CONFIG_Semantic.find(semantic);
			if (semRst != CONFIG_Semantic.end())
			{
				m_semanticMap[name] = semRst->second;
				m_paramMap[name] = MaterialParam(uType);
				return;
			}
			// for common parameters
			m_paramMap[name] = MaterialParam(uType, raw_value);
		}
		SemanticType MaterialParamMap::getSemantic(const std::string& name) const
		{
			auto rst = m_semanticMap.find(name);
			if (rst == m_semanticMap.end()) return render::SemanticNone;
			return rst->second;
		}

		UniformTypeMap StructParam::getUniformTypeMap()
		{
			UniformTypeMap uMap;
			for (auto iter = m_paramMap.begin(); iter != m_paramMap.end(); ++iter)
			{
				uMap[iter->first] = iter->second.m_type;
			}
			return uMap;
		}
		StructParam StructParam::getStructParam(const LightConfig& config, const std::string& baseName)
		{
			StructParam param;
			std::string subBaseName = baseName + ".dir_light";
			param.unionMap(getStructParam(config.dir_light, subBaseName));
			int index = 0;
			for (auto iter = config.point_lights.begin(); iter != config.point_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << baseName.c_str() << ".point_lights" << "[" << index << "]";
				subBaseName = ss.str();
				param.unionMap(getStructParam(*iter, subBaseName));
			}
			index = 0;
			for (auto iter = config.spot_lights.begin(); iter != config.spot_lights.end(); ++iter, ++index)
			{
				std::stringstream ss;
				ss << baseName << ".spot_lights" << "[" << index << "]";
				subBaseName = ss.str();
				param.unionMap(getStructParam(*iter, subBaseName));
			}
			param.setParam(baseName + ".point_light_num", int(config.point_lights.size()));
			param.setParam(baseName + ".spot_light_num", int(config.spot_lights.size()));
			return param;
		}
		StructParam StructParam::getStructParam(const BaseLight& light, const std::string& baseName)
		{
			auto param =  StructParam();
			param.setParam(baseName + ".color", light.color);
			param.setParam(baseName + ".ambiance_intensity", light.ambiance_intensity);
			param.setParam(baseName + ".diffuse_intensity", light.diffuse_intensity);
			return param;
		}
		StructParam StructParam::getStructParam(const PointLight& light, const std::string& baseName)
		{
			std::string subBaseName = baseName + ".base_light";
			auto param = getStructParam((BaseLight)light, subBaseName);
			param.setParam(baseName + ".position", light.position);
			param.setParam(baseName + ".atten.constant", light.atten.constant);
			param.setParam(baseName + ".atten.linear", light.atten.linear);
			param.setParam(baseName + ".atten.exp", light.atten.exp);
			return param;
		}
		StructParam StructParam::getStructParam(const DirectionLight& light, const std::string& baseName)
		{
			std::string subBaseName = baseName + ".base_light";
			auto param = getStructParam((BaseLight)light, subBaseName);
			param.setParam(baseName + ".direction", light.direction);
			return param;
		}
		StructParam StructParam::getStructParam(const SpotLight& light, const std::string& baseName)
		{
			std::string subBaseName = baseName + ".base_light";
			auto param = getStructParam((BaseLight)light, subBaseName);
			param.setParam(baseName + ".direction", light.direction);
			param.setParam(baseName + ".cutoff", light.cutoff);
			return param;
		}
	}
}
