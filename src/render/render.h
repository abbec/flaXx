#ifndef RENDER_H
#define RENDER_H

#include <tr1/memory>
#include "SDL.h"

#include "util/options.h"

namespace flaXx {

class Render
{

public:
    // Konstruktorer
    Render() {}


    void setOptions(std::tr1::shared_ptr<Options> o) {
        options = o;
    }

    void render();

    void saveToFile();

private:
	std::tr1::shared_ptr<Options> options;
};

} // end namespace flaXx

#endif
