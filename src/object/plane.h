#ifndef PLANE_H
#define PLANE_H

#include "object/object.h"
#include "math/vector3f.h"

namespace flaXx
{

class Ray;

class Plane : public Object
{
  public:
	Plane (Vector3f, Vector3f, Vector3f, Vector3f, std::tr1::shared_ptr<Material>);

	virtual Vector3f intersect(Ray &ray);
	virtual Vector3f getNormal(Vector3f &point);

  private:
	/** Triangel 1 har punkterna v1, v2 och v3.
	 * Triangel 2 har punkterna v3, v4 och v1. */
	Vector3f v1, v2, v3, v4;
	Vector3f normal;

};

} // end namespace flaXx
#endif // end PLANE_H
