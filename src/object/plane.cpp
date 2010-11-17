#include "object/plane.h"
#include "render/ray.h"

using namespace flaXx;

Plane::Plane (Vector3f _v1, Vector3f _v2, Vector3f _v3, Vector3f _v4, 
			  std::tr1::shared_ptr<Material> m) : Object(m), v1(_v1), v2(_v2), v3(_v3), v4(_v4)
{
	// Beräkna normal för planet
	normal = v1.cross(v2);
}

Vector3f Plane::intersect(Ray &ray)
{
	// Gör för båda trianglarna i planet
	// TODO: Förberäkna u och v: http://www.devmaster.net/wiki/Ray-triangle_intersection

	// barycentric coordinates
	double distance = -((ray.getStart()-v1)*normal/(ray.getDirection()*normal));

	// Om avståndet är mindre än 0 kan vi fortsätta med nästa triangel
	if (distance >= 0)
	{
		Vector3f point = ray.getStart() + distance*ray.getDirection();

		double u = (point.getY()*v3.getX() - point.getX()*v3.getY())/
			(v2.getY()*v3.getX() - v2.getX()*v3.getY());

		double v = (point.getY()*v2.getX() - point.getX()*v2.getY())/
			(v3.getY()*v2.getX() - v3.getX()*v2.getY());

		if (u >= 0.0 && v >= 0.0 && u+v <= 1.0)
			return point;

	}
	
	distance = -((ray.getStart()-v3)*normal/(ray.getDirection()*normal));

	if (distance >= 0)
	{
		Vector3f point = ray.getStart() + distance*ray.getDirection();

		double u = (point.getY()*v1.getX() - point.getX()*v1.getY())/
			(v4.getY()*v1.getX() - v4.getX()*v1.getY());

		double v = (point.getY()*v4.getX() - point.getX()*v4.getY())/
			(v1.getY()*v4.getX() - v1.getX()*v4.getY());

		if (u >= 0.0 && v >= 0.0 && u+v <= 1.0)
			return point;

	}
	
	return Vector3f(0.0, 0.0, 0.0);
}


Vector3f Plane::getNormal(Vector3f &point)
{
	return normal;
}
