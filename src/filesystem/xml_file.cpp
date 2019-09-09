#include "xml_file.h"
#include "common/log.h"

bool water::filesystem::XMLFile::do_load()
{
	pugi::xml_parse_result result = m_doc.load_file(m_file_path.c_str());
	if (result) {
		log_info("Success parse file %s", m_file_path.c_str());
		return true;
	}else
	{
		log_error("Failed to parse xml file %s with error(%s)", m_file_path.c_str(), result.description());
		return false;
	}
	return true;
}
