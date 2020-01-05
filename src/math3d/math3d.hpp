#ifndef WATER_MATH3D_H
#define WATER_MATH3D_H

#include <vector>
#include "math3d/matrix.hpp"
#include "math3d/euler_angle.hpp"
#include "math3d/vector.hpp"
#include "math3d/quaternion.hpp"

namespace water {
	namespace math3d
	{
		typedef TVector4<float> Vector4;
		typedef TVector3<float> Vector3;
		typedef TVector2<float> Vector2;
		typedef TMatrix44<float> Matrix;
		typedef TEulerAngle<float> EulerAngle;
		typedef TQuaternion<float> Quaternion;
	}
}
#endif
