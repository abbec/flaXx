#ifndef SPHERE_H
#define SPHERE_H

namespace flaXx
{

class Vector3f;

class Sphere : public Object
{
  public:

	Sphere() : Object(std::tr1::shared_ptr<Material>(new DiffuseMaterial()),
					  radius(1.0), origin(Vector3f(1.0, 1.0, 5.0)) {}
	Sphere(float r, Vector3f o) : radius(r), origin(o) {}

	double getRadius(){ return radius; }

	virtual Vector3f intersect(ray &ray);
	virtual Vector3f getNormal(Vector3f &point);

  private:
	double radius;
	Vector3f origin;

};


} // end namespace flaXx
#endif // end SPHERE_H
