#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <cmath>

namespace flaXx{
class Vector3f
{
  public:
	Vector3f() : x(0), y(0), z(0) {}
	Vector3f(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	
	double squareNorm() const {return x*x + y*y + z*z;}
	double operator*(const Vector3f &rhs) const {return x*rhs.x + y*rhs.y + z*rhs.z;}


	friend Vector3f operator*(double lhs, const Vector3f &rhs) { return Vector3f(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);}
	Vector3f operator*(const double rhs) const {return Vector3f(x*rhs, y*rhs, z*rhs);}

	friend Vector3f operator/(double lhs, const Vector3f &rhs) { return Vector3f(lhs/rhs.x, lhs/rhs.y, lhs/rhs.z);}
	Vector3f operator/(const double rhs) const {return Vector3f(x/rhs, y/rhs, z/rhs);}

	Vector3f cross(const Vector3f &rhs) const {return Vector3f(y*rhs.z-z*rhs.y, x*rhs.z-z*rhs.x, x*rhs.y-y*rhs.x );}
	Vector3f operator-(const Vector3f &rhs) const {return Vector3f(x-rhs.x, y-rhs.y, z-rhs.z);}
	Vector3f operator+(const Vector3f &rhs) const {return Vector3f(x+rhs.x, y+rhs.y, z+rhs.z);}

	void normalize(); 

	bool operator== (const Vector3f &rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); }
	bool operator!= (const Vector3f &rhs) const { return !(*this == rhs); }
	
	bool operator== (const double d) const { return (x==d && y==d && z==d); }
	bool operator!= (const double d) const { return !(*this == rhs); }
	
	Vector3f& operator= (const Vector3f &rhs);
	Vector3f& operator+= (const Vector3f &rhs);

	double getX(){return x;}
	double getY(){return y;}
	double getZ(){return z;}
	void setX(double _x){ x = _x;}
	void setY(double _y){ y = _y;}
	void setZ(double _z){ z = _z;}
	void set(double _x, double _y, double _z){x = _x; y = _y; z = _z;}

	friend std::ostream& operator<<(std::ostream &os, const Vector3f &vec);
		
  private:
	double x;
	double y;
	double z;
};
} // namespace flaXx

#endif // end VECTOR3F_H
