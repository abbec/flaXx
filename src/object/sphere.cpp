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
	return (point-origin).normalize();
}
