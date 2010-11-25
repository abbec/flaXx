#include "object/blinnphong.h"
#include <cmath>

using namespace flaXx;

Vector3f BlinnPhong::brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir)
{
	Vector3f Nn = normal.normalize();
	Vector3f Ln = lightDir.normalize();
	Vector3f thetaN = dir.normalize();
	Vector3f Hn = (Ln + thetaN).normalize();

	return (((specIntensity * getSpecular() * (pow(Nn*Hn, roughness)/(Nn*Ln))) * specColor) + (getDiffuse() * getColor())).colorNormalize();
}
