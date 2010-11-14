#include "object/sphere.h"
#include "math/vector3f.h"

Vector3f flaXx::intersect(ray &ray)
{
	Vector3f dst = ray.getStart() - position;
	float b = dst*ray.getDirection().normalize();
	float c = dst*dst - radius*radius;
	float d = b*b - c;
	return d > 0 ? (ray.getStart() + ray.getDirection()*(- b - sqrt(d))) : Vector3f(0.0, 0.0, 0.0);	
}

Vector3f flaXx::getNormal(Vector3f &point)
{
	return point-position;
}
