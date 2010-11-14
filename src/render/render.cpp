#include <iostream>
#include <ctime>
#include <cstdlib>
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

	// Initiera slumptalsgeneratorn
	srand((unsigned)time(0));

	// Renderingsloopen ska vara här
	Uint32 finalColor = 0; /*SDL_MapRGB( screen->format, 255, 0, 0 );*/
	Uint32 *pixmem32;
	double radiance;

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

			
			// RENDERING
			radiance = 0;

			// Hämta pixelkoordinater
			Vector3f pixelCoord = image.getPixelCoord(x, y);

			// Skjut en stråle genom pixeln
			Ray r(scene.getCameraPosition(), pixelCoord, Vector3f(1.0, 1.0, 1.0) ,1);
			radiance = traceRay(r);

			// Mappa färgerna till ett 32-bitars heltal
			finalColor = SDL_MapRGB( screen->format, floor(radiance.getX()*255.0), 
									 floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0) );
			
			// Spara pixeln i blidplanet
			image.setPixel(finalColor, x, y);

			// Rita pixeln på skärmen
			pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;
			*pixmem32 = finalColor;


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
	// image->saveToFile(options->getOutFile());
    std::cout << "Saving to file..." << std::endl;
}


Vector3f Render::traceRay(Ray &r)
{
	// Hitta den närmaste skärningspunkten med scenen
	intersectionPoint = scene.shootRay(r, currentObject);
	currentNormal = currentObject->getNormal(intersectionPoint);
	currentDir = scene.getCameraPosition()-intersectionPoint;

	if (intersectionPoint != 0)
		return computeRadiance(x, , normal);
	else
		return Vector3f(0.0, 0.0, 0.0);
}

Vector3f Render::computeRadiance()
{
	Vector3f estimatedRadiance;

	estimatedRadiance += directIllumination();
	//estimatedRadiance += indirectIllumination();

	return estimatedRadiance;
}


Vector3f Render::directIllumination()
{
	Vector3f estimatedRadiance, lightDirection;
	int nd = options->getNoShadowRays();

	Ray shadowRay;
	double x, z;

	std::tr1::shared_ptr<Light> light = scene.getLight(0);

	double lightArea = light->getWidth() * light->getHeight();
	Vector3f lightPos = light->getPosition();
	
	// Loopa över alla shadowrays
	for (int i = 0; i < nd; i++)
	{
		// Generera slumptal (Likformigt)
		x = (lightPos.getX()  - light->getWidth()/2) + mc.getUniformNumber()*light->getWidth();
		z = (lightPos.getZ() - light->getHeight()/2) + mc.getUniformNumber()*light->getHeight();

		// Sätt rätt värden på shadow-rayen
		shadowRay.setStart(intersectionPoint);
		lightDirection = Vector3f(x, lightPos.getY(), z) - intersectionPoint;
		shadowRay.setDirection(lightDirection);

		// Beräkna radiance
		estimatedRadiance += light->getColor() * currentObject->getMaterial()->brdf(intersectionPoint, currentDir) * 
			radianceTransfer(shadowRay, light->getNormal())/mc->uniformPdf(y, lightArea, 0);
	}

	// Normalisera med antalet shadowrays
	estimatedRadiance = estimatedRadiance*(1/nd);

	return estimatedRadiance;
}


double Render::radianceTransfer(Ray &shadowRay, Vector3f &lsNormal)
{
	// V(x,y) -- visibility function
	unsigned short int visible = 0;
	if (scene.shootRay(shadowRay) == 0.0)
		visible = 1;

	// Fixa längd och normaliserad vektor mellan lampa och punkten
	double rayLength = shadowRay.getDirection().squareNorm();
	Vector3f psiVector =  shadowRay.getDirection().normalize();

	// G(x,y) -- geometry term
	double geometry = ((currentNormal * psiVector) * (lsNormal * -psiVector))/rayLength;

	// V(x,y) * G(x,y)
	return geometry * visible;
}
