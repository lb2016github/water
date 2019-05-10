#ifndef WATER_TECHNIQUE_H
#define WATER_TECHNIQUE_H
#include "render/render_state_info.h"
#include "render/render_state.h"
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "render/shader_program.h"
#include "render/technique_common.h"


namespace water {
	namespace render {
		struct RenderPass;
		class Technique;
		class TechniqueManager;
		WaterInterface IRenderObject;
		typedef std::shared_ptr<Technique> TechniquePtr;

		struct RenderPass {
			int index;
			RenderState render_state;
			ProgramPtr program;
		};

		class Technique {
		public:
			// not render object immediately, but create RenderTasks and add to RenderTaskManager
			void render(IRenderObject* render_obj);
		private:
			std::string m_filepath;
			std::vector<RenderPass> m_render_pass_queue;	// render queue
		public:
			friend class TechniqueManager;
		};

		class TechniqueManager
		{
		public:
			TechniquePtr get_technique(std::string& file_path);
			static TechniqueManager* get_instance();
		private:
			TechniqueManager() {};
			bool do_load(std::string& file_path);
		private:
			std::map<std::string, TechniquePtr> m_tech_map;
			static TechniqueManager* instance;
		};


	}
}

#endif