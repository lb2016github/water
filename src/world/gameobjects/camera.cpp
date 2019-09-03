#include "camera.h"
#include "world/components/transform_component.h"


namespace water
{
	namespace world
	{
		math3d::Matrix Camera::get_view_matrix()
		{
			TransformComponent* comp = (TransformComponent*)get_component(COMP_TRANSFORMATION);
			math3d::Matrix mtx = comp->get_world_transformation();
			mtx = math3d::inverse(mtx);
			return mtx;
		}
	}
}
