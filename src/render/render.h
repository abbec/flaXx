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

#ifndef RENDER_H
#define RENDER_H

#ifdef _MSC_VER
	#include <memory>
#else
	#include <tr1/memory>
#endif
#include "SDL.h"

#include "util/options.h"
#include "scene/scene.h"
#include "object/object.h"
#include "math/vector3f.h"
#include "math/montecarlo.h"
#include "render/ray.h"
#include "render/imageplane.h"

namespace flaXx {

/**
 * The rendering class keeping track of other classes
 * and containing the main rendering loop.
 * \author Albert Cervin
 * \author Nathalie Ek
 */
class Render
{

public:

    // Constructor
    Render();

	~Render() { SDL_FreeSurface(buffer); SDL_Quit(); /* Exit SDL correctly */}

	/** Method taking a shared pointer to a options object
	 * to use for the rendering.
	 * \param o Options-object to be used.
	 */
    void setOptions(std::tr1::shared_ptr<Options>);

	/** The render method with the main rendering loop. */
    void render();

	/** Save image buffer to file. The filename
	 * is decided by the attribute in the options-object
	 * containg the filename. */
    void saveToFile();

private:

	Vector3f traceRay(Ray &);
	Vector3f computeRadiance(Vector3f &, Vector3f &);
	Vector3f directIllumination(Vector3f &, Vector3f &);
	Vector3f indirectIllumination(Vector3f &, Vector3f &);
	double radianceTransfer(Ray &, Vector3f, Vector3f &);
	double absorption();

	Vector3f getSpecularRay(const Vector3f &, const double);
	Vector3f getDiffuseRay(const Vector3f &);
	Vector3f refract(const Vector3f &normal, const Vector3f &psi, const double eta) const;

	SDL_Surface *createBufferSurface();

	std::tr1::shared_ptr<Options> options;
	std::tr1::shared_ptr<ImagePlane> image;
	Scene scene;
	bool complete;

	// Variable to keep track of current object
	std::tr1::shared_ptr<Object> currentObject;

	unsigned int raylength;

	// Image and screen buffer
	SDL_Surface *screen;
	SDL_Surface *buffer;

};

} // end namespace flaXx

#endif
