#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

class BlinnPhong : public Material
{
  public:
	BlinnPhong(Vector3f c, Vector3f sc, double _kd, double _ks, double r) : 
		Material(c), specColor(sc), kd(_kd), ks(_ks), roughness(r) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double kd, ks, roughness;
	Vector3f specColor;


};

} // end namespace flaXx
#endif // end BLINNPHONG_H
