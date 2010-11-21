#include "vector3f.h"
// using namespace flaXx;

namespace flaXx 
{

Vector3f Vector3f::normalize() const
{
	// Kolla om den redan skulle råka 
	// vara normaliserad
	double sq = squareNorm();
	Vector3f ret = *this/sqrt(sq);

	return ret;
}

Vector3f Vector3f::colorNormalize() const
{
	double max = -1.0;

	max = x;

	if (y > max)
		max = y;

	if (z > max)
		max = z;

	if (max > 1.0)
		return *this/max;
	else
		return *this;
}

Vector3f& Vector3f::operator= (const Vector3f &rhs)
{
	// Handle self assignment
	if (this == &rhs)
		return *this;

	x = rhs.x; y = rhs.y; z = rhs.z;
	return *this;
}

Vector3f& Vector3f::operator= (const double d)
{
	x = d; y = d; z = d;
	return *this;
}

Vector3f& Vector3f::operator+= (const Vector3f &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

std::ostream& operator<<(std::ostream &os, const Vector3f &vec)
{
	os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; 
	return os;
}


} // end namespace flaXx
