#include "object/plane.h"
#include "render/ray.h"

using namespace flaXx;

Plane::Plane (Vector3f _v1, Vector3f _v2, Vector3f _v3, Vector3f _v4, 
			  std::tr1::shared_ptr<Material> m) : Object(m), v1(_v1), v2(_v2), v3(_v3), v4(_v4)
{
	// Beräkna normal för planet
	normal = (v2-v1).cross((v2-v3));
}

Vector3f Plane::intersect(const Ray &ray)
{
	// Gör för båda trianglarna i planet
	// TODO: Förberäkna u och v: http://www.devmaster.net/wiki/Ray-triangle_intersection

	// barycentric coordinates
	Vector3f nnormal = normal.normalize();
	Vector3f nRayDir = ray.getDirection().normalize();

	Vector3f point, i1, i2, i3;
	double dot11, dot12, dot13, dot22, dot23, invDen, u, v;

	double distance = (-((ray.getStart()-v1)*nnormal)/(nRayDir*nnormal));

	// Om avståndet är mindre än 0 kan vi fortsätta med nästa triangel
	if (distance >= 0)
	{
		point = ray.getStart() + nRayDir*distance;

		i1 = v2 - v1;
		i2 = v3 - v1;
		i3 = point - v1;

		dot11 = i1 * i1;
		dot12 = i1 * i2;
		dot13 = i1 * i3;
		dot22 = i2 * i2;
		dot23 = i2 * i3;

		// Barycentric coordinates
		invDen = 1 / (dot11 * dot22 - dot12 * dot12);
		u = (dot22 * dot13 - dot12 * dot23) * invDen;
		v = (dot11 * dot23 - dot12 * dot13) * invDen;

		if (u >= 0 && v >= 0 && u+v <=1)
			return point;
	}
	
	distance = (-((ray.getStart()-v3)*nnormal)/(nRayDir*nnormal));

	if (distance >= 0)
	{
		point = ray.getStart() + nRayDir*distance;

		i1 = v1 - v3;
		i2 = v4 - v3;
		i3 = point - v3;

		dot11 = i1 * i1;
		dot12 = i1 * i2;
		dot13 = i1 * i3;
		dot22 = i2 * i2;
		dot23 = i2 * i3;

		// Barycentric coordinates
		invDen = 1 / (dot11 * dot22 - dot12 * dot12);
		u = (dot22 * dot13 - dot12 * dot23) * invDen;
		v = (dot11 * dot23 - dot12 * dot13) * invDen;

		if (u >= 0 && v >= 0 && u+v <=1)
			return point;

	}
	
	return Vector3f(0.0, 0.0, 0.0);
}

Vector3f Plane::getNormal(Vector3f &point)
{
	return normal;
}
