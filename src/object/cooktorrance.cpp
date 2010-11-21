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

	return (getColor()*kd) + (((0.5/M_PI) * (D*G)/((Nn*Ln)*(Nn*thetaN)))*specColor);
}
