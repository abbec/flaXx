#include <iostream>
#include "render/render.h"

using namespace flaXx;

void Render::render()
{
    std::cout << "Render..." << std::endl;
	
	// Ordna ett SDL-fönster för att visa
	// progress för renderingen.
	SDL_Surface *screen;
	SDL_Init(SDL_INIT_VIDEO);
	// TODO: Ersätt 1024 och 768 med korrekta värden
	// från optionsobjektet.
	screen = SDL_SetVideoMode(options->getWidth(), 
							  options->getHeight(),
							  32, SDL_HWSURFACE);

	// Renderingsloopen ska vara här
	Uint32 color = (Uint32) SDL_MapRGB( screen->format, 255, 0, 0 );
	Uint32 *pixmem32;

	if(SDL_MUSTLOCK(screen)) 
	{
		if(SDL_LockSurface(screen) < 0) 
			return;
	}

	std::cout << screen->pitch << ", " << screen->format->BytesPerPixel << std::endl;

	for (int y = 0; y<options->getHeight(); y++)
	{
		for (int x = 0; x<options->getWidth(); x++)
		{
			//pixmem32 = ((Uint32*) screen->pixels) + (y*screen->pitch) + (x*4);
			//*pixmem32 = color;

			//SDL_Flip(screen);

		}

	}

	if(SDL_MUSTLOCK(screen)) 
		SDL_UnlockSurface(screen);

	// Avsluta SDL
	SDL_Quit();
	
}

void Render::saveToFile()
{
    std::cout << "Saving to file..." << std::endl;
}
