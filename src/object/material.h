#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/vector3f.h"

namespace flaXx
{

class Material
{
  public:
	Material (Vector3f c) : color(c) {}

	virtual double brdf(const Vector3f &point, const Vector3f &dir) = 0;

	Vector3f getColor() { return color; }

  private:
	Vector3f color;

};

} // end namespace flaXx
#endif // end MATERIAL_H
