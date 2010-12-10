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

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <cmath>

namespace flaXx{
class Vector3f
{
  public:
	Vector3f() : x(0.0), y(0.0), z(0.0) {}
	Vector3f(double d) : x(d), y(d), z(d) {}
	Vector3f(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	Vector3f(const Vector3f &v) : x(v.x), y(v.y), z(v.z) {}
	
	double squareNorm() const {return x*x + y*y + z*z;}
	double operator*(const Vector3f &rhs) const { return x*rhs.x + y*rhs.y + z*rhs.z; }

	Vector3f mtimes(const Vector3f &rhs) const { return Vector3f(x*rhs.x, y*rhs.y, z*rhs.z);}

	friend Vector3f operator*(double lhs, const Vector3f &rhs) { return Vector3f(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);}
	Vector3f operator*(const double rhs) const {return Vector3f(x*rhs, y*rhs, z*rhs);}

	friend Vector3f operator/(double lhs, const Vector3f &rhs) { return Vector3f(lhs/rhs.x, lhs/rhs.y, lhs/rhs.z);}
	Vector3f operator/(const double rhs) const {return Vector3f(x/rhs, y/rhs, z/rhs);}

	Vector3f cross(const Vector3f &rhs) const {return Vector3f(y*rhs.z-z*rhs.y, -(x*rhs.z-z*rhs.x), x*rhs.y-y*rhs.x );}
	Vector3f operator-(const Vector3f &rhs) const {return Vector3f(x-rhs.x, y-rhs.y, z-rhs.z);}
	friend Vector3f operator-(const Vector3f &rhs) {return Vector3f(-rhs.x, -rhs.y, -rhs.z);}
	Vector3f operator+(const Vector3f &rhs) const {return Vector3f(x+rhs.x, y+rhs.y, z+rhs.z);}

	Vector3f normalize() const;

	Vector3f colorNormalize() const;

	double sum() const { return x+y+z; }

	bool operator== (const Vector3f &rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); }
	bool operator!= (const Vector3f &rhs) const { return !(*this == rhs); }
	
	bool operator== (const double d) const { return (x==d && y==d && z==d); }
	bool operator!= (const double d) const { return !(*this == d); }
	
	Vector3f& operator= (const Vector3f &rhs);
	Vector3f& operator= (const double d);
	Vector3f& operator+= (const Vector3f &rhs);

	bool operator>=(const double d) const { return (x >= d && y >= d && z >= d); }

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	void setX(const double _x) { x = _x;}
	void setY(const double _y) { y = _y;}
	void setZ(const double _z) { z = _z;}
	void set(const double _x, const double _y, const double _z){x = _x; y = _y; z = _z;}

	friend std::ostream& operator<<(std::ostream &os, const Vector3f &vec);
		
  private:
	double x;
	double y;
	double z;
};
} // namespace flaXx

#endif // end VECTOR3F_H
