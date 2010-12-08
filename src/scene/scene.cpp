#include "scene/scene.h"
#include <limits>
#include <cstdlib>
#include "object/cooktorrance.h"
#include "object/blinnphong.h"

flaXx::Scene::Scene() : 
	camera(Camera(Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 1.0), 1.0)),
	lights(new std::vector<std::tr1::shared_ptr<Light> >()),
	objects(new std::list<std::tr1::shared_ptr<Object> >())
{
	// Create default scene
	std::cout << "Construcing example scene.";


	// Two area lights
	lights->reserve(2);

	lights->push_back(std::tr1::shared_ptr<Light> (new Light(Vector3f(0.0, 19.0, 5.0),
															Vector3f(0.0, -1.0, 0.0),
															Vector3f(1.0, 0.5, 1.0),
															1.5, 1.5)));

	lights->push_back(std::tr1::shared_ptr<Light> (new Light(Vector3f(0.0, 29.0, 35.0),
															Vector3f(0.0, -1.0, 0.0),
															Vector3f(1.0, 1.0, 1.0),
															1.5, 1.5)));
	

	// Eight Corners
	Vector3f c1(-40.0, 30.0, 0.0);
	Vector3f c2(0.0, 30.0, 40.0);
	Vector3f c3(-40.0, -10.0, 0.0);
	Vector3f c4(0.0, -10.0, 40.0);

	Vector3f c5(40.0, 30.0, 0.0);
	Vector3f c6(40.0, -10.0, 0.0);

	Vector3f c7(0.0, -10.0, 0.0);
	Vector3f c8(0.0, 30.0, 0.0);

	std::cout << ".";

	// Wall materials
	std::tr1::shared_ptr<Material> wall_mtrl1(new DiffuseMaterial(Vector3f(1.0, 1.0, 1.0), 0.8));
	std::tr1::shared_ptr<Material> wall_mtrl2(new DiffuseMaterial(Vector3f(201.0/255.0, 0.0, 137.0/255.0), 0.8));
	std::tr1::shared_ptr<Material> wall_mtrl3(new DiffuseMaterial(Vector3f(1.0, 1.0, 1.0), 0.8));

	// Left wall
	objects->push_back(std::tr1::shared_ptr<Object> (new Plane(c1, c3, c4, c2, wall_mtrl1)));

	// Right wall
	objects->push_back(std::tr1::shared_ptr<Object> (new Plane(c5, c2, c4, c6, wall_mtrl1)));

	// Floor
	objects->push_back(std::tr1::shared_ptr<Object> (new Plane(c7, c6, c4, c3, wall_mtrl1)));

	// Roof
	objects->push_back(std::tr1::shared_ptr<Object> (new Plane(c8, c1, c2, c5, wall_mtrl3)));

	std::cout << ".";

	// Object definitions
	std::tr1::shared_ptr<Material> sphere_mtrl(new BlinnPhong(Vector3f(1.0, 1.0, 1.0), Vector3f(1.0, 1.0, 1.0), 0.1, 1.0, 2000, 100));
	sphere_mtrl->setTransmission(1.0, 0.645);


	std::tr1::shared_ptr<Material> sphere_mtrl2(new DiffuseMaterial(Vector3f(236.0/255.0, 146/255.0, 74.0/255.0), 0.5));

	objects->push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(0.0, 0.0, 25.0), 5.0, sphere_mtrl)));

	for (int i = -10; i <= 10; i+=5)
		objects->push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(i*0.75, 0.0, 36.0 - abs(i)), 1.0, sphere_mtrl2)));

	std::tr1::shared_ptr<Material> sphere_mtrl3(new BlinnPhong(Vector3f(1.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0), 0.1, 0.7, 2000, 100));

	objects->push_back(std::tr1::shared_ptr<Object> (new Sphere(Vector3f(0.0, -7.0, 15.0), 3.0, sphere_mtrl3)));

	std::cout << " Done!" << std::endl;

}

/*flaXx::Scene(std::string filename)
{
	// Parse XML file to read scene
	

	}*/

flaXx::Scene::ShootReturn flaXx::Scene::shootRay(flaXx::Ray &r)
{

	// Traverse all objects and test intersection
	Vector3f intersectionPoint, nearestPoint;
	std::tr1::shared_ptr<Object> currObj;
	double distance, shortestDistance = std::numeric_limits<double>::max();

	for (std::list< std::tr1::shared_ptr<Object> >::iterator it = objects->begin(); it != objects->end(); it++)
	{
		intersectionPoint = (*it)->intersect(r);

		if (intersectionPoint != 0.0)
		{
			distance = (intersectionPoint - r.getStart()).squareNorm();

			// TODO: BSP tree or something like it :)
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


