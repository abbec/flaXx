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

#ifndef OBJECT_H
#define OBJECT_H

#include <tr1/memory>

#include "object/material.h"

namespace flaXx
{

// Forward declarations
class Ray;
class Vector3f;

class Object
{
  public:
	Object(std::tr1::shared_ptr<Material> m) : material(m){}

	virtual ~Object(){}

	virtual Vector3f intersect(const Ray &ray) = 0;
	virtual Vector3f getNormal(Vector3f &point) = 0;

	std::tr1::shared_ptr<Material> getMaterial() { return material; }

  private:
	std::tr1::shared_ptr<Material> material;

};

} // end namespace flaXx
#endif // end OBJECT_H
