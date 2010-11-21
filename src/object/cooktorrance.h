#ifndef COOKTORRANCE_H
#define COOKTORRANCE_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

class CookTorrance : public Material
{
  public:
	CookTorrance(Vector3f c, Vector3f sc, double _kd, double _ks, double r, double _eta) : 
		Material(c), specColor(sc), kd(_kd), ks(_ks), roughness(r), eta(_eta) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double kd, ks, roughness, eta;
	Vector3f specColor;


};

} // end namespace flaXx
#endif // end COOKTORRANCE_H
