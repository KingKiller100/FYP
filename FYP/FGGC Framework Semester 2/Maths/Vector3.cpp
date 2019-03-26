#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <cmath>
#include <complex>

template<class TP>
TP Vector3<TP>::AngleBetweenVectors(const Vector3& v, const Vector3& u, const bool inDegrees)
{
	const float angle = Vector3::DotProduct(v, u) / (Vector3::Magnitude(v) * Vector3::Magnitude(u));
	
	const float toDegrees = 180.f / M_PI;

	return inDegrees ? acos(angle) * toDegrees : acos(angle);
}

template<class TP>
Vector3<TP> Vector3<TP>::CrossProduct(const Vector3& u, const Vector3& v)
{
	return Vector3(u.y * v.z - u.z  * v.y,
		u.z * v.x - u.x * v.z, 
		u.x * v.y - u.y * v.x);
}

template<class TP>
void Vector3<TP>::Truncate(const float max)
{
	if (::fabsf(Vector3::Magnitude(*this)) > max)
		*this = Vector3::Normalize(*this) * max;
}

template <class TP>
void Vector3<TP>::ToPositives()
{
	x < 0 ? x = ::fabsf(x) : x;
	y < 0 ? y = ::fabsf(y) : y;
	z < 0 ? z = ::fabsf(z) : z;
}

