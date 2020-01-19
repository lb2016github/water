#ifndef WATER_MATERIAL_H
#define WATER_MATERIAL_H
#include "common/common.h"
#include "math3d/math3d.hpp"
#include <memory>
#include "render/render.h"
#include "render/draw_command.h"
#include "render/texture.h"
#include "render/light.h"
#include <map>
#include "material_param.h"


namespace water
{
	namespace render
	{
		class Material: public std::enable_shared_from_this<Material>
		{
		public:
			void render(IRenderable* render_obj);
			void render(const MeshDataPtr mesh);
			MaterialParamMapPtr getParamMap(int index);
			void setParamMap(int index, MaterialParamMapPtr param_map);
			unsigned int getParamMapCount();
			void setTechnique(const std::string& tech_filepath);

			static std::map<int, MaterialPtr> loadFromFile(const std::string& filepath);
		private:
			TechniquePtr m_tech;
			std::map<int, MaterialParamMapPtr> m_matParamMap;
		};
	}
}

#endif // !WATER_MATERIAL_H
