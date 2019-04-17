#ifndef WATER_XML_FILE_H
#define WATER_XML_FILE_H
#include "filesystem/file_base.h"
#include "pugixml/pugixml.hpp"

namespace water {
	namespace filesystem {
		class XMLFile : public FileBase {
		public:
			virtual bool do_load();

		private:
			pugi::xml_document m_doc;

		};
	}
}
#endif // !WATER_XML_FILE_H
