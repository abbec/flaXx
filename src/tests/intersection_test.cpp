#include <iostream>

#include "object/sphere.h"
#include "object/plane.h"
#include "math/vector3f.h"
#include "render/ray.h"

#include <tr1/memory>
#include "object/material.h"

using namespace flaXx;

int main()
{
	Sphere s(Vector3f(-2.0, -2.0, 15.0), 3.0, std::tr1::shared_ptr<Material>());

	// Planets fyra hörnpunkter
	Vector3f upLeft(-20.0, 20.0, 1.0);
	Vector3f upRight(20.0, 20.0, 1.0);
	Vector3f downRight(20.0, -20.0, 1.0);
	Vector3f downLeft(-20.0, -20.0, 1.0);

	Plane p(downLeft, downRight, upRight, upLeft, std::tr1::shared_ptr<Material>());

	// En ray som skär
	Ray is(Vector3f(-2.0, 0.9, 15.0), Vector3f(0.0, -1.0, 0.0), Vector3f(1.0), 1.0);
	is.setStart(is.getStart() + is.getDirection()*0.01);

	// En som inte gör det
	//Ray nis(Vector3f(0.0, 0.0, 14.1), Vector3f(0.0, 0.0, 1.0), Vector3f(1.0), 1.0);

	std::cout << s.intersect(is) << std::endl;

	return 0;
}
