#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "object/material.h"
#include "math/vector3f.h"

namespace flaXx
{

class DiffuseMaterial : public Material
{
  public:

	DiffuseMaterial() : Material(Vector3f(0.5, 0.5, 0.5), 0.5, 0.0) {}
	DiffuseMaterial(Vector3f c, double kd) : Material(c, kd, 0.0) {}
	
	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

};


} // end namespace flaXx
#endif // end DIFFUSE_H
