#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/vector3f.h"

namespace flaXx
{

class Material
{
  public:
	Material (Vector3f c, double _kd, double _ks) : color(c), mirror(false), transparent(false), kd(_kd), ks(_ks) {}

	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir) = 0;

	Vector3f getColor() { return color; }

	void setMirror(bool m) { mirror = m; }
	void setTransparent(bool t) { transparent = t; }


	bool isMirror() { return mirror; }
	bool isTransparent() { return transparent; }
	double getSpecular() { return ks; }
	double getDiffuse() { return kd; }

  private:
	Vector3f color;
	double ks, kd;
	bool mirror, transparent;

};

} // end namespace flaXx
#endif // end MATERIAL_H
