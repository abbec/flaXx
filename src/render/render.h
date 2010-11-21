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

	~Render() { SDL_Quit(); /* Avsluta SDL Korrekt */}

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
	bool absorption();

	std::tr1::shared_ptr<Options> options;
	std::tr1::shared_ptr<ImagePlane> image;
	Scene scene;
	bool complete;

	// Olika variabler för att hålla reda på vilket objekt vi jobbar med
	std::tr1::shared_ptr<Object> currentObject;
	Vector3f currentNormal;
	Vector3f currentDir;
	Vector3f intersectionPoint;

	unsigned int raylength;

	// Bildbuffern
	SDL_Surface *screen;

};

} // end namespace flaXx

#endif
