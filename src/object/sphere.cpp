#include "object/sphere.h"

flaXx::Vector3f flaXx::Sphere::intersect(const flaXx::Ray &ray)
{
	Vector3f rayDir = ray.getDirection().normalize();
	flaXx::Vector3f dst = origin - ray.getStart();
	double b = dst*(rayDir);
	double radiusSquared = radius*radius;
	double dstSquared = dst.squareNorm();

	if (b < 0 && dstSquared > radiusSquared)
		return Vector3f(0.0);

	double c = dstSquared - b*b;

	if (c > radiusSquared)
		return Vector3f(0.0);

	double d = sqrt(radiusSquared-c);

	return  (ray.getStart() + rayDir*(b + (dstSquared > radiusSquared ? -d : d )));	
}

flaXx::Vector3f flaXx::Sphere::getNormal(flaXx::Vector3f &point)
{
	return point-origin;
}
