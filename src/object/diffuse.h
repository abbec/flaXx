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

#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "object/material.h"
#include "math/vector3f.h"

namespace flaXx
{

class DiffuseMaterial : public Material
{
  public:

	DiffuseMaterial() : Material(Vector3f(0.5, 0.5, 0.5), 0.5, 0.0) {}
	DiffuseMaterial(Vector3f c, double kd) : Material(c, kd, 0.0) {}
	
	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

};


} // end namespace flaXx
#endif // end DIFFUSE_H
