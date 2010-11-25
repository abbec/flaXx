#ifndef COOKTORRANCE_H
#define COOKTORRANCE_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

class CookTorrance : public Material
{
  public:
	CookTorrance(Vector3f c, double kd, double ks, Vector3f sc, double rough, double _eta) : 
		Material(c, kd, ks), specColor(sc), roughness(rough), eta(_eta) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double kd, ks, roughness, eta;
	Vector3f specColor;


};

} // end namespace flaXx
#endif // end COOKTORRANCE_H
