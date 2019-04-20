#include "technique.h"

void water::render::Technique::load_from_xml(const char * file_path)
{
	m_file.load(file_path);
	if (!m_file.m_loaded) {
		return;
	}
	// load success

}
