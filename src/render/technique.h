#ifndef WATER_TECHNIQUE_H
#define WATER_TECHNIQUE_H
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "render/render.h"
#include "render/draw_command.h"


namespace water {
	namespace render {
		struct RenderPass {
			int index;
			RenderStateInfo render_state;
			ProgramPtr program;
		};

		class Technique {
		public:
			// not render object immediately, but create RenderTasks and add to RenderTaskManager
			void render(IRenderable* render_obj);
			void render(MaterialPtr mat_ptr, MeshDataPtr mesh_ptr);
		private:
			std::string m_filepath;
			std::vector<RenderPass> m_render_pass_queue;	// render queue
		public:
			friend class TechniqueManager;
		};

		class TechniqueManager
		{
		public:
			TechniquePtr get_technique(const std::string& file_path);
			static TechniqueManager* get_instance();
		private:
			TechniqueManager() {};
			bool do_load(const std::string& file_path);
		private:
			std::map<std::string, TechniquePtr> m_tech_map;
			static TechniqueManager* instance;
		};


	}
}

#endif