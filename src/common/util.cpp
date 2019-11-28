#include "util.h"

namespace water {
	WaterID create_id()
	{
		static unsigned long next_id = 0;
		return ++next_id;
	}
}
