#ifndef WATER_MATH3D_H
#define WATER_MATH3D_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <vector>

namespace water {
	namespace math3d
	{
		typedef glm::vec2 Vector2;
		typedef glm::vec3 Vector3;
		typedef glm::vec4 Vector4;
		typedef glm::mat4 Matrix;

		Matrix inline inverse(const Matrix& mat)
		{
			return glm::inverse(mat);
		}

		Matrix inline transpose(const Matrix& mat)
		{
			return glm::inverse(mat);
		}

		Matrix inline get_rotation_matrix(const Vector3& rotation)
		{
			return glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);

		}
		Matrix inline get_translate_matrix(const Vector3& position)
		{
			Matrix tranlate_mtx;
			glm::translate(tranlate_mtx, position);
			return tranlate_mtx;
		}
		Matrix inline get_scale_matrix(const Vector3& scale)
		{
			Matrix scale_mtx;
			glm::scale(scale_mtx, scale);
			return scale_mtx;
		}
		Matrix inline get_transform_matrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
		{
			return get_translate_matrix(position) * get_rotation_matrix(rotation) * get_scale_matrix(scale);
		}
		Matrix inline get_perpective_matrix(float near, float far, float fov_y, float aspect)
		{
			return glm::perspective(fov_y, aspect, near, far);
		}
	}
}
#endif
