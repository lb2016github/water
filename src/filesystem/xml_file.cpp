#include "xml_file.h"
#include "common/log.h"

bool water::filesystem::XMLFile::do_load()
{
	if (!m_doc.load_file(m_file_path.c_str()))
	{
		log_warn("Failed to load xml file: %s", m_file_path);
		return false;
	}
	return true;
}
