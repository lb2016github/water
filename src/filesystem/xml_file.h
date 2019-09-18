#ifndef WATER_XML_FILE_H
#define WATER_XML_FILE_H
#include "filesystem/file_base.h"
#include "pugixml/pugixml.hpp"

namespace water {
	namespace filesystem {
		class XMLFile : public FileBase {
		public:
			using FileBase::FileBase;
			virtual bool do_load();
			pugi::xml_document& get_doc() { return m_doc; }
			pugi::xml_node get_root_node() { return m_doc.root(); }

		private:
			pugi::xml_document m_doc;

		};
	}
}
#endif // !WATER_XML_FILE_H
