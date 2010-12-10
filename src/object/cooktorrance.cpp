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

#include "object/cooktorrance.h"
#include <cmath>

using namespace flaXx;

Vector3f CookTorrance::brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir)
{
	double m2 = roughness * roughness;

	Vector3f Nn = normal.normalize();
	Vector3f Ln = lightDir.normalize();
	Vector3f thetaN = dir.normalize();
	Vector3f Hn = (Ln + thetaN).normalize();

	float t = Hn*Nn; float t2 = t*t;

	double x = -(t2-1)/(t2*m2);

	double D = 1/(m2*t2*t2) * (1 + x + 0.5*x*x + 0.1667*x*x*x);
	

	double G = 1;
	double g =  2*t/(thetaN*Hn);
	double G1 = g*(Nn*thetaN);
	double G2 = g*(Nn*Ln);

	if (G1 < G)
		G = G1;

	if (G2 < G)
		G = G2;

	double beta = Ln * Hn;
	double n2 = 1.0/eta;
	double n1 = 1.0;
	double rp = (n2-n1)/(n2+n1);
	double rs = (n1-n2)/(n1+n2);
	double F = (fabs(rp) * fabs(rp) + fabs(rs)*fabs(rs))/2;

	return (getColor()*getDiffuse()) + getSpecular()*(((0.5/M_PI) * (D*G)/((Nn*Ln)*(Nn*thetaN)))*specColor);
}
