/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "object/plane.h"
#include "render/ray.h"

using namespace flaXx;

Plane::Plane (Vector3f _v1, Vector3f _v2, Vector3f _v3, Vector3f _v4, 
			  std::tr1::shared_ptr<Material> m) : Object(m), v1(_v1), v2(_v2), v3(_v3), v4(_v4)
{
	// Calculate plane normal
	normal = ((v2-v1).cross((v2-v3))).normalize();
}

Vector3f Plane::intersect(const Ray &ray)
{
	// barycentric coordinates
	Vector3f nnormal = normal.normalize();
	Vector3f nRayDir = ray.getDirection().normalize();

	Vector3f point, i1, i2, i3;
	double dot11, dot12, dot13, dot22, dot23, invDen, u, v;

	double distance = (-((ray.getStart()-v1)*nnormal)/(nRayDir*nnormal));

	// If the distance is negative, we can go on with the next triangle
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
		
		// 1.0 + 1e-10 fixes a precision problem
		// on some processors
		if (u >= 0.0 && v >= 0.0 && u+v < 1.0 + 1e-10)
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

		// 1.0 + 1e-10 fixes a precision problem
		// on some processors
		if (u >= 0.0 && v >= 0.0 && u+v < 1 + 1e-10)
			return point;

	}
	
	return Vector3f(0.0, 0.0, 0.0);
}

Vector3f Plane::getNormal(Vector3f &point)
{
	return normal;
}
