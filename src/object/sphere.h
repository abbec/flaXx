#ifndef SPHERE_H
#define SPHERE_H

#include <tr1/memory>

#include "object/object.h"
#include "render/ray.h"
#include "object/diffuse.h"
#include "math/vector3f.h"

namespace flaXx
{

class Sphere : public Object
{
  public:

	Sphere() : Object(std::tr1::shared_ptr<Material>(new DiffuseMaterial())), 
			   radius(1.0), origin(Vector3f(1.0, 1.0, 5.0)) {}
	
	Sphere( Vector3f o, float r, std::tr1::shared_ptr<Material> m) : Object(m),
																	 radius(r), 
																	 origin(o) {}

	double getRadius(){ return radius; }

	virtual Vector3f intersect(const Ray &ray);
	virtual Vector3f getNormal(Vector3f &point);

  private:
	double radius;
	Vector3f origin;

};


} // end namespace flaXx
#endif // end SPHERE_H
