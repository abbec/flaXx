#include "scene/scene.h"

flaXx::Scene::Scene() : 
camera(Camera(Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 1.0), 1.0))
{
	// Skapa standardobjekt i scenen
	std::cout << "Construcing example scene.";


	// En arealampa
	lights.reserve(1);

	lights.push_back(std::tr1::shared_ptr<Light> (new Light(Vector3f(0.0, 39.9, 20.0),
															Vector3f(0.0, -1.0, 0.0),
															Vector3f(0.0, -1.0, 0.0),
															2.0, 2.0)));

	// Fyra plan (rummet)

	// Åtta Hörn
	Vector3f c1(-20.0, 0.0, 0.0);
	Vector3f c2(-20.0, 0.0, 40.0);
	Vector3f c3(-20.0, 40.0, 40.0);
	Vector3f c4(-20.0, 40.0, 0.0);

	Vector3f c5(20.0, 0.0, 40.0);
	Vector3f c6(20.0, 40.0, 40.0);

	Vector3f c7(20.0, 0.0, 0.0);
	Vector3f c8(20.0, 40.0, 0.0);

	std::cout << ".";

	// Material för väggen
	std::tr1::shared_ptr<Material> wall_mtrl(new DiffuseMaterial());

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
	std::tr1::shared_ptr<Material> sphere_mtrl(new DiffuseMaterial(Vector3f(1.0, 0.0, 0.0), 0.6));
	
	objects.push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(4.0, 2.0, 5.0), 1.0, sphere_mtrl)));
	objects.push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(1.0, 2.0, 10.0), 0.5, sphere_mtrl)));

	std::cout << " Done!" << std::endl;

}

flaXx::Vector3f flaXx::Scene::shootRay(flaXx::Ray &r)
{
	
	// Gå igenom alla objekt och undersök
	// kollision.
	Vector3f intersectionPoint, nearestPoint;
	double distance, shortestDistance = 0;
	
	for (std::list< std::tr1::shared_ptr<Object> >::iterator it = objects.begin(); it != objects.end(); it++)
	{
		intersectionPoint = (*it)->intersect(r);

		if (intersectionPoint != Vector3f(0.0, 0.0, 0.0))
		{
			distance = (intersectionPoint - r.getStart()).squareNorm();

			// BSP-träd eller nåt för detta kanske? :) 
			if (distance < shortestDistance || shortestDistance == 0)
			{
				shortestDistance = distance;
				nearestPoint = intersectionPoint;
			}
		}	
	}

	return nearestPoint;
}

flaXx::Vector3f flaXx::Scene::shootRay(flaXx::Ray &r, std::tr1::shared_ptr<Object> o)
{
	// Gå igenom alla objekt och undersök
	// kollision.
	Vector3f intersectionPoint, nearestPoint;
	double distance, shortestDistance = 0;
	
	for (std::list< std::tr1::shared_ptr<Object> >::iterator it = objects.begin(); it != objects.end(); it++)
	{
		intersectionPoint = (*it)->intersect(r);

		if (intersectionPoint != Vector3f(0.0, 0.0, 0.0))
		{
			distance = (intersectionPoint - r.getStart()).squareNorm();

			// BSP-träd eller nåt för detta kanske? :) 
			if (distance < shortestDistance || shortestDistance == 0)
			{
				shortestDistance = distance;
				nearestPoint = intersectionPoint;
				o = *it;
			}
		}	
	}

	return nearestPoint;

}

