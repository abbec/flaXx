#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "object/material.h"
#include "math/vector3f.h"

namespace flaXx
{

class DiffuseMaterial : public Material
{
  public:

	DiffuseMaterial() : Material(Vector3f(0.5, 0.5, 0.5)), reflectance(0.5) {}
	DiffuseMaterial(Vector3f c, double r) : Material(c), reflectance(r) {}
	
	double getReflectance() { return reflectance; }
	void setReflectance(double r) { reflectance = r; }
	
	virtual double brdf(const Vector3f &point, const Vector3f &dir);

  private:
	double reflectance;

};


} // end namespace flaXx
#endif // end DIFFUSE_H
