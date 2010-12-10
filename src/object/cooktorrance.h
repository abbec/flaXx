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

#ifndef COOKTORRANCE_H
#define COOKTORRANCE_H

#include "math/vector3f.h"
#include "object/material.h"

namespace flaXx
{

class CookTorrance : public Material
{
  public:
	CookTorrance(Vector3f c, double kd, double ks, Vector3f sc, double rough, double _eta) : 
		Material(c, kd, ks), specColor(sc), roughness(rough), eta(_eta) {}


	virtual Vector3f brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir);

  private:
	double kd, ks, roughness, eta;
	Vector3f specColor;


};

} // end namespace flaXx
#endif // end COOKTORRANCE_H
