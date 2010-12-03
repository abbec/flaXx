#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/vector3f.h"

namespace flaXx
{

class Material
{
  public:
	Material (Vector3f c, double _kd, double _ks) : color(c), mirror(false), transmission(0.0), kd(_kd), ks(_ks), eta(0.0) {}

	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir) = 0;

	Vector3f getColor() { return color; }

	void setMirror(bool m) { mirror = m; }
	void setTransmission(double t, double e) { transmission = t; eta = e; }


	bool isMirror() { return mirror; }
	bool isTransparent() { return (transmission > 0.0); }
	double getSpecular() { return ks; }
	double getDiffuse() { return kd; }
	double getEta() { return eta; }
	double getTransmission() { return transmission; }

  private:
	Vector3f color;
	double ks, kd, eta, transmission;
	bool mirror;

};

} // end namespace flaXx
#endif // end MATERIAL_H
