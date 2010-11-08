#ifndef FLAXX_MAIN_H
#define FLAXX_MAIN_H

#include <tr1/memory>

#include "util/commandLineParser.h"
#include "render/render.h"

namespace flaXx
{


/** Själva applikationsklassen som innehåller den "riktiga"
 * main-metoden. */
class FlaxxMain
{
  public:
	/** Main-metoden som styr programmet. */
    int main (int argc, char *argv[]);
	
	/** Metod som returnerar en instans av klassem (om den existerar). */
    static std::tr1::shared_ptr<FlaxxMain> instance();

  private:
    /** Privat singleton-konstruktor */
    FlaxxMain();

    CommandLineParser cmdParser;
	std::tr1::shared_ptr<Render> render;

    /// Singletoninstansen
    static std::tr1::shared_ptr<FlaxxMain> inst;
};

} // namespace flaXx
#endif
