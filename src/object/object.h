#ifndef OBJECT_H
#define OBJECT_H

#include <tr1/memory>

#include "object/material.h"

namespace flaXx
{

class Ray;

class Vector3f;

class Object
{
  public:
	Object(std::tr1::shared_ptr<Material> m) : material(m){}

	virtual ~Object(){}

	virtual Vector3f intersect(const Ray &ray) = 0;
	virtual Vector3f getNormal(Vector3f &point) = 0;

	std::tr1::shared_ptr<Material> getMaterial() { return material; }

  private:
	std::tr1::shared_ptr<Material> material;

};

} // end namespace flaXx
#endif // end OBJECT_H
