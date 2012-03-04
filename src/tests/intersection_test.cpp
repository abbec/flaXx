#include <iostream>

#include "object/sphere.h"
#include "object/plane.h"
#include "math/vector3f.h"
#include "render/ray.h"

#ifdef WIN32
	#include <memory>
#else
	#include <tr1/memory>
#endif
#include "object/material.h"

using namespace flaXx;

Vector3f refract(const Vector3f &normal, const Vector3f &psi, const double eta)
{
	Vector3f psiN = psi.normalize();
	Vector3f Nx = normal.normalize();

	double cosi = -(Nx*psiN);

	// Calculate refraction dir
	double cost2 =  1-eta*eta*(1-(cosi*cosi));
	
	// Brewster's angle
	if (cost2 < 0.0)
		return Vector3f(0.0);

	double beta = 0.0;

	beta = sqrtf(float(cost2));		

	return ((eta*psiN) + (eta*cosi-beta)*Nx).normalize();
}

int main()
{
	Sphere s(Vector3f(0.0, 0.0, 5.0), 3.0, std::tr1::shared_ptr<Material>());

	// Planets fyra hörnpunkter
	Vector3f upLeft(-20.0, 20.0, 10.0);
	Vector3f upRight(20.0, 20.0, 10.0);
	Vector3f downRight(20.0, -20.0, 10.0);
	Vector3f downLeft(-20.0, -20.0, 10.0);

	Plane p(downLeft, downRight, upRight, upLeft, std::tr1::shared_ptr<Material>());

	// En ray som skär
	Ray is(Vector3f(0.0), Vector3f(-0.5, 0.0, 1.0));

	// En som inte gör det
	//Ray nis(Vector3f(0.0, 0.0, 14.1), Vector3f(0.0, 0.0, 1.0));

	Vector3f x = s.intersect(is);

	std::cout << "Intersects in: " << x;

	
	Vector3f normal = s.getNormal(x);

	std::cout << " where normal is: " << normal << std::endl;
	
	Vector3f refr = refract(normal, is.getDirection(), 0.645);

	std::cout << "Refraction dir: " << refr << std::endl;

	is.setStart(x+refr*0.01);
	is.setDirection(refr);

	x = s.intersect(is);

	std::cout << "Hits on the other side in: " << x;

	normal = -s.getNormal(x);

	std::cout << " where normal is: " << normal << std::endl;

	refr = refract(normal, is.getDirection(), 1.0/0.645);

	std::cout << "Refraction dir: " << refr << std::endl;

	is.setStart(x+refr*0.01);
	is.setDirection(refr);


	x = p.intersect(is);

	std::cout << "Intersects plane in " << x << std::endl;

	return 0;
}
