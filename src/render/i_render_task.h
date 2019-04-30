#ifndef WATER_TECHNIQUE_H
#define WATER_TECHNIQUE_H
#include "render/render_state_info.h"
#include <map>
#include <string>
#include <vector>


namespace water {
	namespace render {
		struct RenderPass {
			int index;
			std::map<ShaderType, std::string> shaders;
			RenderState render_state;
		};

		class Technique {
		public:
			void load(const char* file_path);
		private:
			std::string m_filepath;
			std::vector<RenderPass> m_render_pass_queue;	// render queue
		};

	}
}

#endif