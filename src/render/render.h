#ifndef RENDER_H
#define RENDER_H

#include <tr1/memory>
#include "SDL.h"

#include "util/options.h"

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
    Render() {}

	/** Metod som tar in en delad pekare till ett Options-objekt
	 * som ska användas vid renderingen.
	 * \param o Options-objektet som ska användas.
	 */
    void setOptions(std::tr1::shared_ptr<Options> o) { options = o; }

	/** Själva renderingsmetoden med renderingsloopen. */
    void render();

	/** Spara ImageFilmen till en fil. Filnamnet
	 * bestäms av options-objektets attribut
	 * för utfilnamn. */
    void saveToFile();

private:
	std::tr1::shared_ptr<Options> options;
};

} // end namespace flaXx

#endif
