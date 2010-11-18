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
	Ray is(Vector3f(0.0, 0.0, 10.0), Vector3f(0.0, 1.0, 0.0), Vector3f(1.0), 1.0);

	// En som inte gör det
	//Ray nis(Vector3f(0.0, 0.0, 14.1), Vector3f(0.0, 0.0, 1.0), Vector3f(1.0), 1.0);

	int correct = 0;

	unsigned int num_tests = 6;
	for (int i = 0; i < 6; i++)
	{

		is.setStart(Vector3f(-1.0 + (1.0/(double)num_tests)*i, 0.0, 10.0));

		Vector3f point = s.intersect(is);

		if (point != Vector3f(0.0))
		{
			std::cout << "Intersecting the sphere: " << point << ": CORRECT" << std::endl;
			correct++;
		}
		else
			std::cerr << "Not intersecting: WRONG!" << std::endl;
	}


	return 0;
}
