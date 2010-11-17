#include "object/diffuse.h"
#include <cmath>

double flaXx::DiffuseMaterial::brdf(const flaXx::Vector3f &point, const flaXx::Vector3f &dir)
{
	return reflectance/M_PI;
}
