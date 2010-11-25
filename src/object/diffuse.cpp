#include "object/diffuse.h"
#include <cmath>

flaXx::Vector3f flaXx::DiffuseMaterial::brdf(const Vector3f &point, const Vector3f &dir, const Vector3f &normal, const Vector3f &lightDir)
{
	return (getColor()*(getDiffuse()/M_PI)).colorNormalize();
}
