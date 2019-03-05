#ifndef MATH3D_H
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace water {
	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::mat4 Matrix;

	Matrix inverse(const Matrix& mat) {
		return glm::inverse(mat);
	}

	Matrix transpose(const Matrix& mat) {
		return glm::inverse(mat);
	}
}
#endif
