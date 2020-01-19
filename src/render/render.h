#ifndef WATER_RENDER_H
#define WATER_RENDER_H
#include <memory>
#include <vector>
#include "common/common.h"
#include "render/render_const.h"
#include "mesh.h"
#include "render/technique_common.h"

namespace water
{
	namespace render
	{
		// Material
		class Material;
		typedef std::shared_ptr<Material> MaterialPtr;

		// Techinque
		class Technique;
		typedef std::shared_ptr<Technique> TechniquePtr;
		class TechniqueManager;

		// Render Task 
		WaterInterface IRenderTask;
		typedef std::shared_ptr<IRenderTask> RenderTaskPtr;
		typedef std::vector<RenderTaskPtr> RenderTaskList;
		class RenderTaskManager;

		// Render Program
		WaterInterface IProgramManager;
		typedef std::shared_ptr<IProgramManager> ProgramManagerPtr;
		WaterInterface IRenderProgram;
		typedef std::shared_ptr<IRenderProgram> ProgramPtr;
		typedef unsigned int ShaderObject;
		typedef std::map<std::string, ShaderObject> ShaderMap;
		#define UNDEFINED_SHADER -1

		// Render Object and Mesh 
		WaterInterface IRenderable;

		// Render State
		WaterInterface IRenderStateManager;
		typedef std::shared_ptr<IRenderStateManager> RenderStateManagerPtr;

		// Define locations of attributes
		enum ATTRIBUTE_LOCATION {
			LOCATION_POSITION = 0,
			LOCATION_NORMAL,
			LOCATION_COLOR,
			LOCATION_COORDINATE,
			LOCATION_TANGENT,
			LOCATION_LENGTH,
		};
	}
}

#endif //!WATER_RENDER_H