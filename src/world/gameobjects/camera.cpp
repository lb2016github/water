#include "camera.h"
#include "world/components/transform_component.h"


namespace water
{
	namespace world
	{
		math3d::Matrix Camera::get_view_matrix()
		{
			auto comp = GET_COMPONENT(this, TransformComponent);
			math3d::Matrix mtx = comp->get_world_transformation();
			mtx = math3d::inverse(mtx);
			return mtx;
		}
		math3d::Matrix Camera::get_projection_matrix()
		{
			// TODO
			return math3d::Matrix();
		}
	}
}
