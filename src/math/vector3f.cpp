/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "vector3f.h"
// using namespace flaXx;

namespace flaXx 
{

Vector3f Vector3f::normalize() const
{
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
