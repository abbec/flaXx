#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

class BlinnPhong : public Material
{
  public:
	BlinnPhong(Vector3f c, Vector3f sc, double kd, double ks, double r, double i) : 
		Material(c, kd, ks), specColor(sc), roughness(r), specIntensity(i) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double roughness, specIntensity;
	Vector3f specColor;


};

} // end namespace flaXx
#endif // end BLINNPHONG_H
