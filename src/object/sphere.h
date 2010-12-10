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
