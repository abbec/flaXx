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

#include "object/blinnphong.h"
#include <cmath>

using namespace flaXx;

Vector3f BlinnPhong::brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir)
{
	Vector3f Nn = normal.normalize();
	Vector3f Ln = lightDir.normalize();
	Vector3f thetaN = dir.normalize();
	Vector3f Hn = (Ln + thetaN).normalize();

	float i = powf((float) (Nn*Hn), (float) roughness);

	Vector3f ret = getSpecular()*i*specColor*specIntensity + getDiffuse()*getColor();

	return ret.colorNormalize();
}
