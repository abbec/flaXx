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

#ifndef PLANE_H
#define PLANE_H

#include "object/object.h"
#include "math/vector3f.h"

namespace flaXx
{

class Ray;

class Plane : public Object
{
  public:
	Plane (Vector3f, Vector3f, Vector3f, Vector3f, std::tr1::shared_ptr<Material>);

	virtual Vector3f intersect(const Ray &ray);
	virtual Vector3f getNormal(Vector3f &point);

  private:
	/** Triangle 1 has points v1, v2 och v3.
	 * Triangle 2 has points v3, v4 och v1. */
	Vector3f v1, v2, v3, v4;
	Vector3f normal;

};

} // end namespace flaXx
#endif // end PLANE_H
