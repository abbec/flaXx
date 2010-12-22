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

#include "scene/light.h"
#include "render/ray.h"

using namespace flaXx;


/*Vector3f Light::intersect(const Ray &ray)
{
	// Do for both triangles in plane
	Vector3f v1 = Vector3f(position.getX()-width/2.0, position.getY(), position.getZ()-height/2.0);
	Vector3f v2 = Vector3f(position.getX()-width/2.0, position.getY(), position.getZ()+height/2.0);
	Vector3f v3 = Vector3f(position.getX()+width/2.0, position.getY(), position.getZ()+height/2.0);
	Vector3f v4 = Vector3f(position.getX()+width/2.0, position.getY(), position.getZ()-height/2.0);

	// barycentric coordinates
	Vector3f nnormal = direction.normalize();
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
		
		// 1.0 + 1e-10 fixar ett precisions-problem
		// med vissa processorer
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

		// 1.0 + 1e-10 fixar ett precisions-problem
		// med vissa processorer
		if (u >= 0.0 && v >= 0.0 && u+v < 1 + 1e-10)
			return point;

	}
	
	return Vector3f(0.0, 0.0, 0.0);

}*/
