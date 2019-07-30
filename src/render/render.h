#ifndef WATER_RENDER_H
#define WATER_RENDER_H
#include <memory>
#include <vector>
#include "common/common.h"
#include "render/render_state_info.h"
#include "render/technique_common.h"

namespace water
{
	namespace render
	{
		// Material
		class Material;
		typedef std::shared_ptr<Material> MaterialPtr;
		struct ParameterMap;

		// Techinque
		class Technique;
		typedef std::shared_ptr<Technique> TechniquePtr;
		class TechniqueManager;

		// Render Task 
		WaterInterface RenderTask;
		typedef std::shared_ptr<RenderTask> RenderTaskPtr;
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
		WaterInterface IMesh;
		WaterInterface IRenderObject;
		typedef std::shared_ptr<IMesh> MeshPtr;

		// Render State
		WaterInterface IRenderStateManager;
		typedef std::shared_ptr<IRenderStateManager> RenderStateManagerPtr;
	}
}

#endif //!WATER_RENDER_H