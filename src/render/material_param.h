#ifndef WATER_MATERIAL_PARAM_H
#include "math3d/math3d.hpp"
#include <vector>
#include <string>
#include "texture.h"
#include "technique_common.h"

namespace water
{
	namespace render
	{
		template<class T>
		struct TSimpleParam
		{
			TSimpleParam(const std::string& str)
			{
				loadFromString();
			}
			TSimpleParam(T value) : m_value(value) {}
			TSimpleParam(const TSimpleParam<T>& param) : m_value(param.m_value) {}
			void loadFromString(const std::string& str)
			{
				loadFromString(str, m_value);
			}
			T m_value;
		};
		typedef TSimpleParam<int> IntParam;
		typedef TSimpleParam<float> FloatParam;
		typedef TSimpleParam <math3d::Vector2> Vector2Param;
		typedef TSimpleParam <math3d::Vector3> Vector3Param;
		typedef TSimpleParam <math3d::Matrix> MatrixParam;
		typedef TSimpleParam <TexturePtr> TextureParam;

		template<class T>
		struct TArrayParam
		{
			TArrayParam() {}
			TArrayParam(const TArrayParam<T>& param)
			{
				m_value = param.m_value;
			}
			TArrayParam(TArrayParam<T>&& param)
			{
				m_value = std::move(param.m_value);
			}
			std::vector<T> m_value;
		};
		typedef TArrayParam<math3d::Matrix> MatrixArrayParam;

		void loadFromString(const std::string& str, int& value);
		void loadFromString(const std::string& str, float& value);
		void loadFromString(const std::string& str, math3d::Vector2& value);
		void loadFromString(const std::string& str, math3d::Vector3& value);
		void loadFromString(const std::string& str, math3d::Matrix& value);
		void loadFromString(const std::string& str, TexturePtr& value);

		struct MaterialParam
		{
			template<UniformType type, class T>
			MaterialParam(T value);
			MaterialParam(UniformType pType, const std::string& str);
			MaterialParam(const MaterialParam& param);
			MaterialParam(MaterialParam&& param);
			~MaterialParam();
			MaterialParam& operator=(const MaterialParam& param);
			MaterialParam& operator=(MaterialParam&& param);

			template<UniformType type, class T>
			void setValue(const T& value);

			UniformType m_type;
			union
			{
				void* m_data;
				IntParam* m_intParam;
				FloatParam* m_floatParam;
				Vector2Param* m_vec2Param;
				Vector3Param* m_vec3Param;
				MatrixParam* m_mtxParam;
				TextureParam* m_texParam;
				MatrixArrayParam* m_mtxArrayParam;
			};

		private:
			/*
			init data with param
			*/
			void _initData(const  MaterialParam& param);
			/*
			release data
			*/
			void _releaseData();
		};

		/*
		map of material parameter
		*/
		struct MaterialParamMap
		{
			// check has certern parameter
			bool has_param(const std::string& name);
			// set param
			void set_param(const std::string& name, const MaterialParam& pvalue);
			void set_param(const std::string& name, int value);
			void set_param(const std::string& name, float value);
			void set_param(const std::string& name, const math3d::Matrix& value);
			void set_param(const std::string& name, const math3d::Vector3& value);
			void set_param(const std::string& name, const math3d::Vector2& value);
			// set texture
			void set_texture(const std::string& name, TexturePtr tex_ptr);
			// set param value with str_value and type, which is called when param value is read from material file
			void set_raw_param(const std::string& name, const std::string& type, const std::string& raw_value, const std::string& semantic);
			// get value type of param
			ParamValueType get_value_type(const std::string& name) const;
			// get semantic of param by name
			SemanticType get_semantic(const std::string& name) const;

			/* map of parameters */
			std::map<std::string, MaterialParam> m_paramMap;
			// map of {name: semantic}
			std::map<std::string, SemanticType> m_semantic_map;

		};
		
		template<UniformType type, class T>
		inline MaterialParam::MaterialParam(T value)
		{
			setValue<type>(value);
		}

		template<UniformType type, class T>
		inline void MaterialParam::setValue(const T& value)
		{
			if (type == m_type && m_data)
			{
				*(T*)m_data = value;
				return;
			}
			m_type = type;
			if (m_data)
			{
				_releaseData();
			}
			switch (type)
			{
			case UniformType::TypeFloat :
				m_floatParam = new FloatParam(value);
				break;
			case UniformType::TypeInt:
				m_intParam = new IntParam(value);
				break;
			case UniformType::TypeMatrix:
				m_mtxParam = new MatrixParam(value);
				break;
			case UniformType::TypeVector2:
				m_vec2Param = new Vector2Param(value);
				break;
			case UniformType::TypeVector3:
				m_vec3Param = new Vector3Param(value);
				break;
			case UniformType::TypeCubeMap:
			case UniformType::TypeSampler2D:
				m_texParam = new TextureParam(value);
				break;
			case UniformType::TypeMatrixArray:
				m_mtxArrayParam = new MatrixArrayParam(value);
				break;
			default:
				log_error("Unkown type: %d", type);
				break;
			}
		}

}
}


#endif // !WATER_MATERIAL_PARAM_H
