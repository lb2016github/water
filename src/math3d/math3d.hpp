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

		template<class T>
		T inline identity()
		{
			return glm::identity<T>();
		}

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
			return glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);

		}
		Matrix inline get_translate_matrix(const Vector3& position)
		{
			return glm::translate(glm::identity<Matrix>(), position);
		}
		Matrix inline get_scale_matrix(const Vector3& scale)
		{
			return glm::scale(glm::identity<Matrix>(), scale);
		}
		Matrix inline get_transform_matrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
		{
			return get_translate_matrix(position) * get_rotation_matrix(rotation) * get_scale_matrix(scale);
		}
		Matrix inline get_perpective_matrix(float near, float far, float fov_y, float aspect)
		{
			return glm::perspective(glm::radians(fov_y), aspect, near, far);
		}
		Matrix inline ortho(float left, float right, float up, float down)
		{
			return glm::ortho<float>(left, right, up, down);
		}
		Matrix inline look_at(const Vector3& eye, const Vector3& center, const Vector3& up)
		{
			return glm::lookAt(eye, center, up);
		}
		Matrix inline eular_angle_yx(const Vector2& xy)
		{
			return glm::eulerAngleYX(xy.x, xy.y);
		}
		Vector3 inline get_forward(const Matrix& rotation_mtx)
		{
			Vector3 forward = { rotation_mtx[2][0], rotation_mtx[2][1], rotation_mtx[2][2] };
			return glm::normalize(forward);
		}
		Vector3 inline get_right(const Matrix& rotation_mtx)
		{
			Vector3 right = { rotation_mtx[0][0], rotation_mtx[0][1], rotation_mtx[0][2] };
			return glm::normalize(right);
		}
	}
}
#endif
