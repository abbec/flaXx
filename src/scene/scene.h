/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

/** Class to represent a
 * scene. */
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

	/** Default-constructor that creates our
	 * example scene. */
	Scene();

	ShootReturn shootRay(Ray &);

	Vector3f getCameraPosition() { return camera.getPosition(); }

	std::tr1::shared_ptr<Light> getLight(unsigned int lightNum) { return lights->at(lightNum);}
	int getNumLights() { return lights->size(); }

  private:

	Camera camera;
	std::tr1::shared_ptr< std::vector< std::tr1::shared_ptr<Light> > > lights;
	std::tr1::shared_ptr< std::list< std::tr1::shared_ptr<Object> > > objects;

};

} // end namespace flaXx
#endif // SCENE_H
