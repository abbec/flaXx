#ifndef FLAXX_MAIN_H
#define FLAXX_MAIN_H

#include <tr1/memory>

#include "util/commandLineParser.h"
#include "render/render.h"

namespace flaXx
{

class FlaxxMain
{
public:
    int main (int argc, char *argv[]);
	
    static std::tr1::shared_ptr<FlaxxMain> instance();

private:
    // Privat kostruktor eftersom klassen är
    // singleton.
    FlaxxMain();

    CommandLineParser cmdParser;
	std::tr1::shared_ptr<Render> render;

    // Singletoninstansen
    static std::tr1::shared_ptr<FlaxxMain> inst;
};

} // namespace flaXx
#endif
