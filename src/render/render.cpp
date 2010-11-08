#include <iostream>
#include "render/render.h"

using namespace flaXx;

void Render::render()
{
	std::cout << "Render..." << std::endl;
	
	/* Ordna ett SDL-fönster för att visa
	 * progress för renderingen. */
	SDL_Surface *screen;
	SDL_Init(SDL_INIT_VIDEO);

	// Skapa SDL-yta
	screen = SDL_SetVideoMode(options->getWidth(), 
							  options->getHeight(),
							  32, SDL_HWSURFACE);

	// Renderingsloopen ska vara här
	Uint32 color = (Uint32) SDL_MapRGB( screen->format, 255, 0, 0 );
	Uint32 *pixmem32;

	for (int y = 0; y<options->getHeight(); y++)
	{
		for (int x = 0; x<options->getWidth(); x++)
		{
			// Lås skärmen innan vi ritar upp pixeln
			if(SDL_MUSTLOCK(screen)) 
			{
				if(SDL_LockSurface(screen) < 0) 
					return;
			}

			pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;
			*pixmem32 = color;


			/* Lås upp skärmen och uppdatera pixeln på skärmen.
			 * Det här är lite korkat... Skulle förmodligen kunna 
			 * göras ganska mycket bättre.
			 */
			if(SDL_MUSTLOCK(screen)) 
				SDL_UnlockSurface(screen);

			SDL_UpdateRect(screen, x, y, 1, 1);

		}

	}

	// Avsluta SDL
	SDL_Quit();
	
}

void Render::saveToFile()
{
    std::cout << "Saving to file..." << std::endl;
}
