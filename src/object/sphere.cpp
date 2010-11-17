#include "object/sphere.h"

flaXx::Vector3f flaXx::Sphere::intersect(flaXx::Ray &ray)
{
	flaXx::Vector3f dst = ray.getStart() - origin;
	double b = dst*(ray.getDirection().normalize());
	double c = dst*dst - radius*radius;
	double d = b*b - c;
	return d > 0 ? (ray.getStart() + ray.getDirection()*(- b - sqrt(d))) : Vector3f(0.0, 0.0, 0.0);	
}

flaXx::Vector3f flaXx::Sphere::getNormal(flaXx::Vector3f &point)
{
	return point-origin;
}
