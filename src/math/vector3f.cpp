#include "vector3f.h"
// using namespace flaXx;

namespace flaXx 
{

void Vector3f::normalize()
{
	// Kolla om den redan skulle råka 
	// vara normaliserad
	double sq = squareNorm();
	
	if (sq != 1.0)
		*this/sqrt(squareNorm());
}


Vector3f& Vector3f::operator= (Vector3f &rhs)
{
	// Handle self assignment
	if (this == &rhs)
		return *this;

	x = rhs.x; y = rhs.y; z = rhs.z;
	return *this;
}

Vector3f& Vector3f::operator+= (Vector3f &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this
}

std::ostream& operator<<(std::ostream &os, const Vector3f &vec)
{
	os << "(" << vec.x << "," << vec.y << "," << vec.z << ")"; 
	return os;
}


} // end namespace flaXx
