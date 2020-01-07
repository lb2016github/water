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
		typedef TVector2<int> Vector2I;
		typedef TMatrix44<float> Matrix;
		typedef TQuaternion<float> Quaternion;
		/*
		define extrinsic rotation with y->x->z
		*/
		typedef TEulerAngle<float, EulerType::YXZ> GEulerAngle;
		/*
		define intrinsic rotation with y->x->z, which equals to extrinsic rotation z->x->y
		*/
		typedef TEulerAngle<float, EulerType::ZXY> LEulerAngle;

		template<class T>
		T radian(T angle)
		{
			return TO_RAD(angle);
		}

		template<class T>
		T angle(T radian)
		{
			return TO_ANGLE(radian);
		}
	}
}
#endif
