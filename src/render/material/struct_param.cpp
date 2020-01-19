#include "struct_param.h"

namespace water
{
	namespace render
	{
		StructParam::StructParam()
		{
		}
		StructParam::StructParam(const StructParam& param):
			m_mapPtr(param.m_mapPtr)
		{
		}
	}
}
