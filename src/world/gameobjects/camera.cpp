#include "camera.h"
#include "components/transform_component.h"


namespace water
{
	namespace world
	{
		Camera & Camera::operator=(const Camera & camera)
		{
			if (&camera == this) return *this;
			GameObject::operator=(camera);

			// TODO add camera related codes

			return *this;
		}
		Camera::~Camera()
		{
		}
		math3d::Matrix Camera::get_view_matrix()
		{
			TransformComponent* comp = (TransformComponent*)get_component(COMP_TRANSFORMATION);
			math3d::Matrix mtx = comp->get_world_transformation();
			mtx = math3d::inverse(mtx);
			return mtx;
		}
	}
}
