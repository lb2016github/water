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
		typedef Material* MaterialPtr;
		struct ParameterMap;

		// Techinque
		class Technique;
		typedef std::shared_ptr<Technique> TechniquePtr;
		class TechniqueManager;

		// Render Task 
		WaterInterface IRenderTask;
		typedef std::vector<IRenderTask*> RenderTaskList;
		class RenderTaskManager;

		// Render Program
		WaterInterface IProgramManager;
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
	}
}

#endif //!WATER_RENDER_H