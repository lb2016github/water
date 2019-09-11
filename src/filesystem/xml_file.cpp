#include "xml_file.h"
#include "common/log.h"
#include "filesystem/filesystem.h"

bool water::filesystem::XMLFile::do_load()
{
	auto abs_path = FileSystem::get_instance()->get_absolute_path(m_file_path.c_str());
	pugi::xml_parse_result result = m_doc.load_file(abs_path.c_str());
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
