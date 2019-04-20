#ifndef WATER_TECHNIQUE_H
#define WATER_TECHNIQUE_H
#include "render/render_state.h"
#include "filesystem\xml_file.h"


namespace water {
	namespace render {

		class Technique {
		public:
			void load_from_xml(const char* file_path);
		public:
			RenderState* render_state;
			filesystem::XMLFile m_file;

		};

	}
}

#endif