#ifndef SCENE_H
#define SCENE_H

#include <tr1/memory>
#include <list>
#include <vector>

#include "scene/camera.h"
#include "scene/light.h"
#include "math/vector3f.h"
#include "render/ray.h"
#include "object/object.h"
#include "object/sphere.h"
#include "object/plane.h"

namespace flaXx
{

/** Klass för att representera en
 * scen. */
class Scene
{
  public:

	class ShootReturn
	{
	  public:
		ShootReturn(Vector3f p, std::tr1::shared_ptr<Object> o):
			point(p), obj(o) {}

		std::tr1::shared_ptr<Object> getObject() { return obj; }
		Vector3f getPoint() { return point; }
		
	  private:
		std::tr1::shared_ptr<Object> obj;
		Vector3f point;
	};

	/** Default-konstruktor som skapar vår
	 * exempelscen. */
	Scene();

	/** Metod som skapar en ray
	 * och skjuter den in i scenen. Den går
	 * sedan igenom alla objekt och kontrollerar
	 * intersection. Returnerar sedan punkten. */
	ShootReturn shootRay(Ray &);

	Vector3f getCameraPosition() { return camera.getPosition(); }

	std::tr1::shared_ptr<Light> getLight(unsigned int lightNum) { return lights.at(lightNum);}

  private:

	Camera camera;
	std::vector< std::tr1::shared_ptr<Light> > lights;
	std::list< std::tr1::shared_ptr<Object> > objects;

};

} // end namespace flaXx
#endif // SCENE_H
