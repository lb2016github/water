#ifndef WATER_MATERIAL_PARAM_H
#define WATER_MATERIAL_PARAM_H
#include "math3d/math3d.hpp"
#include <vector>
#include <string>
#include "render/texture.h"
#include "render/technique_common.h"
#include "common/common.h"
#include "light.h"

namespace water
{
	namespace render
	{
		struct StructParam;
		/*
		struct of Material Param, which can save data of any types of param
		*/
		struct MaterialParam
		{
			typedef std::vector<math3d::Matrix> MatrixArray;

			MaterialParam(UniformType type = UniformType::TypeNone);
			MaterialParam(int value);
			MaterialParam(float value);
			MaterialParam(const math3d::Vector2& vec2);
			MaterialParam(const math3d::Vector3& vec3);
			MaterialParam(const math3d::Matrix& mtx);
			MaterialParam(const MatrixArray& mtxArray);
			MaterialParam(const StructParam& param);
			MaterialParam(TexturePtr texPtr);
			MaterialParam(UniformType typem, const std::string& str);

			MaterialParam(const MaterialParam& param);
			MaterialParam(MaterialParam&& param);
			~MaterialParam();
			MaterialParam& operator=(const MaterialParam& param);
			MaterialParam& operator=(MaterialParam&& param);

			void setValue(TexturePtr texPtr);
			void setValue(StructParam structParam);
			template<class T>
			void setValue(UniformType type, T& value);


			UniformType m_type;
			union
			{
				void* m_data;
				int* m_int;
				float* m_float;
				math3d::Vector2* m_vec2;
				math3d::Vector3* m_vec3;
				math3d::Matrix* m_mtx;
				TexturePtr m_tex;
				MatrixArray* m_mtxArray;
				StructParam* m_struct;
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
		struct MaterialParamMap : public std::enable_shared_from_this<MaterialParamMap>
		{
			MaterialParamMap();
			MaterialParamMap(const MaterialParamMap& matParamMap);
			MaterialParamMap(MaterialParamMap&& matParamMap);
			MaterialParamMap& operator=(const MaterialParamMap& matParamMap);
			MaterialParamMap& operator=(MaterialParamMap&& matParamMap);
			/*
			merge another MaterialParamMap
			*/
			void unionMap(const MaterialParamMap& paramMap);
			// check has certern parameter
			bool hasParam(const std::string& name);
			// set param
			void setParam(const std::string& name, const MaterialParam& pvalue);
			void setParam(const std::string& name, int value);
			void setParam(const std::string& name, float value);
			void setParam(const std::string& name, const math3d::Matrix& value);
			void setParam(const std::string& name, const math3d::Vector3& value);
			void setParam(const std::string& name, const math3d::Vector2& value);
			void setParam(const std::string& name, const MaterialParam::MatrixArray& value);
			void setParam(const std::string& name, TexturePtr tex_ptr);
			void setParam(const std::string& name, StructParam& value);
			// get param
			const MaterialParam* getParam(const std::string& name);
			/*
			get uniform type map
			*/
			std::map<std::string, UniformType> getUniformMap();
			/*
			set param value with str_value and type, which is called when param value is read from material file
			*/
			void setRawParam(const std::string& name, const std::string& type, const std::string& raw_value, const std::string& semantic);
			// get semantic of param by name
			SemanticType getSemantic(const std::string& name) const;

			/* map of parameters */
			std::map<std::string, MaterialParam> m_paramMap;
			// map of {name: semantic}
			std::map<std::string, SemanticType> m_semanticMap;
		};
		DECL_SHARED_PTR(MaterialParamMap);
		
		/*
		parameter of stuct, which consists of mutiple params, such as light
		*/
		struct StructParam: public MaterialParamMap
		{
			/*
			get uniform type map
			*/
			UniformTypeMap getUniformTypeMap();

			/*
			get StructParam with different objects
			*/
			static StructParam getStructParam(const LightConfig& config, const std::string& baseName);
			static StructParam getStructParam(const BaseLight& light, const std::string& baseName);
			static StructParam getStructParam(const PointLight& light, const std::string& baseName);
			static StructParam getStructParam(const DirectionLight& light, const std::string& baseName);
			static StructParam getStructParam(const SpotLight& light, const std::string& baseName);
		};

	}
}


#endif // !WATER_MATERIAL_PARAM_H
