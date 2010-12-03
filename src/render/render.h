#ifndef RENDER_H
#define RENDER_H

#include <tr1/memory>
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
 * Renderingsklassen som håller koll på alla andra
 * resurser och inhyser även renderingsloopen.
 * \author Albert Cervin
 * \author Nathalie Ek
 */
class Render
{

public:

    // Konstruktorer
    Render();

	~Render() { SDL_FreeSurface(buffer); SDL_Quit(); /* Avsluta SDL Korrekt */}

	/** Metod som tar in en delad pekare till ett Options-objekt
	 * som ska användas vid renderingen.
	 * \param o Options-objektet som ska användas.
	 */
    void setOptions(std::tr1::shared_ptr<Options>);

	/** Själva renderingsmetoden med renderingsloopen. */
    void render();

	/** Spara ImageFilmen till en fil. Filnamnet
	 * bestäms av options-objektets attribut
	 * för utfilnamn. */
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

	// Olika variabler för att hålla reda på vilket objekt vi jobbar med
	std::tr1::shared_ptr<Object> currentObject;

	unsigned int raylength;

	// Bildbuffern
	SDL_Surface *screen;
	SDL_Surface *buffer;

};

} // end namespace flaXx

#endif
