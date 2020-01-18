#include "material_param.h"
#include "boost/algorithm/string.hpp"
#include "common/log.h"

namespace water
{
	namespace render
	{
		MaterialParam::MaterialParam(int value) :
			m_type(UniformType::TypeInt)
		{
			m_intParam = new IntParam(value);
		}
		MaterialParam::MaterialParam(UniformType pType, const std::string& str):
			m_type(pType), m_data(nullptr)
		{
			switch (m_type)
			{
				case UniformType::TypeFloat :
					m_floatParam = new FloatParam(str);
					break;
				case UniformType::TypeInt:
					m_intParam = new IntParam(str);
					break;
				case UniformType::TypeMatrix:
					m_mtxParam = new MatrixParam(str);
					break;
				case UniformType::TypeVector2:
					m_vec2Param = new Vector2Param(str);
					break;
				case UniformType::TypeVector3:
					m_vec3Param = new Vector3Param(str);
					break;
				case UniformType::TypeCubeMap:
				case UniformType::TypeSampler2D:
					m_texParam = new TextureParam(str);
					break;
				case UniformType::TypeMatrixArray:
					m_mtxArrayParam = new MatrixArrayParam();
					break;
				case UniformType::TypeStuct:
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
					delete m_floatParam;
					break;
				case UniformType::TypeInt:
					delete m_intParam;
					break;
				case UniformType::TypeMatrix:
					delete m_mtxParam;
					break;
				case UniformType::TypeVector2:
					delete m_vec2Param;
					break;
				case UniformType::TypeVector3:
					delete m_vec3Param;
					break;
				case UniformType::TypeCubeMap:
				case UniformType::TypeSampler2D:
					delete m_texParam;
					break;
				case UniformType::TypeMatrixArray:
					delete m_mtxArrayParam;
					break;
				default:
					log_error("Unkown type: %d", m_type);
					break;
				}
			}
		}
		void MaterialParam::_initData(const MaterialParam& param)
		{
			switch (param.m_type)
			{
			case UniformType::TypeFloat :
				m_floatParam = new FloatParam(*param.m_floatParam);
				break;
			case UniformType::TypeInt:
				m_intParam = new IntParam(*param.m_intParam);
				break;
			case UniformType::TypeMatrix:
				m_mtxParam = new MatrixParam(*param.m_mtxParam);
				break;
			case UniformType::TypeVector2:
				m_vec2Param = new Vector2Param(*param.m_vec2Param);
				break;
			case UniformType::TypeVector3:
				m_vec3Param = new Vector3Param(*param.m_vec3Param);
				break;
			case UniformType::TypeCubeMap:
			case UniformType::TypeSampler2D:
				m_texParam = new TextureParam(*param.m_texParam);
				break;
			case UniformType::TypeMatrixArray:
				m_mtxArrayParam = new MatrixArrayParam(*param.m_mtxArrayParam);
				break;
			default:
				log_error("Unkown type: %d", param.m_type);
				break;
			}
		}
		void loadFromString(const std::string& str, TexturePtr& value)
		{
			std::vector<std::string> sub_values;
			boost::split(sub_values, str, boost::is_space());
			auto texPtr = std::make_shared<TextureData>();
			switch (sub_values.size())
			{
			case 1:
				texPtr->tex_type = TEXTURE_2D;
				break;
			case 6:
				texPtr->tex_type = TEXTURE_CUBE;
				break;
			default:
				log_error("Failed to load texture from string as the num of textures is %d", sub_values.size());
				return;
			}
			for each (auto path in sub_values)
			{
				auto img_ptr = std::make_shared<filesystem::Image>();
				img_ptr->load(path);
				texPtr->images.push_back(img_ptr);
			}
			value = TextureManager::get_instance()->get_texture(texPtr);
		}
		bool MaterialParamMap::has_param(const std::string& name)
		{
			return m_paramMap.find(name) != m_paramMap.end();
		}
		void MaterialParamMap::set_param(const std::string& name, const MaterialParam& pvalue)
		{
			m_paramMap[name] = pvalue;
		}
		void MaterialParamMap::set_param(const std::string& name, int value)
		{
			m_paramMap[name] = MaterialParam(UniformType::TypeInt, value);
		}
}
}
