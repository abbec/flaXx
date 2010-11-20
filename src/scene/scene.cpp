#include "scene/scene.h"
#include <limits>

flaXx::Scene::Scene() : 
camera(Camera(Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 1.0), 1.0))
{
	// Skapa standardobjekt i scenen
	std::cout << "Construcing example scene.";


	// En arealampa
	lights.reserve(1);

	lights.push_back(std::tr1::shared_ptr<Light> (new Light(Vector3f(0.0, 19.0, 20.0),
															Vector3f(0.0, -1.0, 0.0),
															Vector3f(1.0, 1.0, 1.0),
															2.0, 2.0)));

	// Fyra plan (rummet)

	// Åtta Hörn
	Vector3f c1(-20.0, -20.0, 0.0);
	Vector3f c2(-20.0, -20.0, 40.0);
	Vector3f c3(-20.0, 20.0, 40.0);
	Vector3f c4(-20.0, 20.0, 0.0);

	Vector3f c5(20.0, -20.0, 40.0);
	Vector3f c6(20.0, 20.0, 40.0);

	Vector3f c7(20.0, -20.0, 0.0);
	Vector3f c8(20.0, 20.0, 0.0);

	std::cout << ".";

	// Material för väggen
	std::tr1::shared_ptr<Material> wall_mtrl(new DiffuseMaterial(Vector3f(0.0, 0.0, 1.0), 0.4));

	// Vänstra väggen
	objects.push_back(std::tr1::shared_ptr<Object> (new Plane(c1, c2, c3, c4, wall_mtrl)));
	
	// Bakre väggen
	objects.push_back(std::tr1::shared_ptr<Object> (new Plane(c2, c5, c6, c3, wall_mtrl)));

	// Högra väggen
	objects.push_back(std::tr1::shared_ptr<Object> (new Plane(c5, c7, c8, c6, wall_mtrl)));

	// Golvet
	objects.push_back(std::tr1::shared_ptr<Object> (new Plane(c2, c1, c7, c5, wall_mtrl)));

	// Taket
	objects.push_back(std::tr1::shared_ptr<Object> (new Plane(c3, c6, c8, c4, wall_mtrl)));

	std::cout << ".";

	// Två sfärer
	std::tr1::shared_ptr<Material> sphere_mtrl(new DiffuseMaterial(Vector3f(1.0, 1.0, 0.0), 0.6));
	std::tr1::shared_ptr<Material> sphere_mtrl2(new DiffuseMaterial(Vector3f(1.0, 0.0, 0.0), 0.8));
	
	objects.push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(-4.0, -2.0, 20.0), 3.0, sphere_mtrl)));
	objects.push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(1.0, 2.0, 30.0), 2.5, sphere_mtrl2)));

	std::cout << " Done!" << std::endl;

}

flaXx::Scene::ShootReturn flaXx::Scene::shootRay(flaXx::Ray &r)
{
	
	// Gå igenom alla objekt och undersök
	// kollision.
	Vector3f intersectionPoint, nearestPoint;
	std::tr1::shared_ptr<Object> currObj;
	double distance, shortestDistance = std::numeric_limits<double>::max();
	
	for (std::list< std::tr1::shared_ptr<Object> >::iterator it = objects.begin(); it != objects.end(); it++)
	{
		intersectionPoint = (*it)->intersect(r);

		if (intersectionPoint != 0.0)
		{
			distance = (intersectionPoint - r.getStart()).squareNorm();

			// BSP-träd eller nåt för detta kanske? :) 
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				nearestPoint = intersectionPoint;
				currObj = *it;
			}
		}	
	}

	return ShootReturn(nearestPoint, currObj);
}

