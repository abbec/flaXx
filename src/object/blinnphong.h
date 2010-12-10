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

#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

/** Implementation of the modified Blinn-Phong
 * model BRDF. */

class BlinnPhong : public Material
{
  public:
	BlinnPhong(Vector3f c, Vector3f sc, double kd, double ks, double r, double i) : 
		Material(c, kd, ks), specColor(sc), roughness(r), specIntensity(i) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double roughness, specIntensity;
	Vector3f specColor;

};

} // end namespace flaXx
#endif // end BLINNPHONG_H
