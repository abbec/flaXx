#include "scene/scene.h"

flaXx::Scene::Scene()
{
	// Skapa standardobjekt i scenen
}

Vector3f flaXx::Scene::shootRay(Ray &r, std::tr1::shared_ptr<Object> o = std::tr1::shared_ptr<Object>(NULL))
{
	// Gå igenom alla objekt och undersök
	// kollision.
	Vector3f intersectionPoint, nearestPoint;
	double distance, shortestDistance = 0;
	
	for (std::list<Object>::iterator it = objects.begin(); it < objects.size(); it++)
	{
		intersectionPoint = it->intersect(ray);

		if (intersectionPoint != Vector3f(0.0, 0.0, 0.0))
		{
			distance = (intersectionPoint - ray.getStart()).squareNorm();

			// BSP-träd eller nåt för detta kanske? :) 
			if (distance < shortestDistance || shortestDistance == 0)
			{
				shortestDistance = distance;
				nearestPoint = intersectionPoint;
				o = std::tr1::shared_ptr<Object>(it);
			}
		}	
	}

	return nearestPoint;

}

