#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "render/render.h"

using namespace flaXx;

Render::Render() : complete(false)
{}

void Render::setOptions(std::tr1::shared_ptr<Options> o)
{
	options = o;

	image = std::tr1::shared_ptr<ImagePlane>(new ImagePlane(M_PI/4.0, o->getWidth(), o->getHeight()));
}

void Render::render()
{
	std::cout << "Creating image plane.";

	/* Ordna ett SDL-fönster för att visa
	 * progress för renderingen. */
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Event event;

	std::cout << ".";

	// Skapa SDL-yta
	screen = SDL_SetVideoMode(options->getWidth(), 
							  options->getHeight(),
							  32, SDL_HWSURFACE);

	SDL_WM_SetCaption("flaXx Monte-Carlo ray tracer", "flaXx"); 
	
	std::cout << ". Done!" << std::endl;

	std::cout << "Render started..." << std::endl;
	
	// Initiera slumptalsgeneratorn
	srand((unsigned)time(0));

	// Renderingsloopen ska vara här
	Uint32 finalColor = 0; /*SDL_MapRGB( screen->format, 255, 0, 0 );*/
	Uint32 *pixmem32;
	Vector3f radiance;
	Vector3f pixelCoord;

	unsigned int totalPixels = options->getHeight()*options->getWidth();

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
			radiance = 0.0;

			// Hämta pixelkoordinater
			pixelCoord = image->getPixelCoord(x, y);

			// Skjut en stråle genom pixeln
			Ray r(scene.getCameraPosition(), pixelCoord, Vector3f(1.0, 1.0, 1.0) ,1);

			radiance = traceRay(r).colorNormalize();

			// Mappa färgerna till ett 32-bitars heltal
			finalColor = SDL_MapRGB( screen->format, floor(radiance.getX()*255.0), 
									 floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0) );

			// Rita pixeln på skärmen/minnet
			pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;
			*pixmem32 = finalColor;


			/* Lås upp skärmen och uppdatera pixeln på skärmen.
			 * Det här är lite korkat... Skulle förmodligen kunna 
			 * göras ganska mycket bättre.
			 */
			if(SDL_MUSTLOCK(screen)) 
				SDL_UnlockSurface(screen);

			SDL_UpdateRect(screen, x, y, 1, 1);


			// Möjlighet att avsluta
			SDL_PollEvent(&event);
			switch(event.type)
			{
			case SDL_QUIT:
				{
					return;
				}
			}
			
		}

	}


	std::cout << "Done! The rendering is finished. To exit and save the render, just close the window. " << std::endl;

	bool exit = false;

	while (!exit)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
			{
				complete = true;
				exit = true;
			}
		}

	}
	
}

void Render::saveToFile()
{

	if (complete)
	{
		std::cout << "Saving to file: " << options->getOutFileName() << std::endl;

		// Skriv till fil
		Uint32 *pixmem32;

		std::ofstream file (options->getOutFileName().c_str(), std::ios::out|std::ios::binary);


	
		// Lås skärmen innan vi ritar upp pixeln
		if(SDL_MUSTLOCK(screen)) 
		{
			if(SDL_LockSurface(screen) < 0) 
				return;
		}

		std::cout << "Screen locked" << std::endl;

		for (int y = 0; y<options->getHeight(); y++)
		{
			for (int x = 0; x<options->getWidth(); x++)
			{

				pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;

				file.write(reinterpret_cast<char*>(*pixmem32), 32);
				std::cout << "HÄR" << std::endl;
			}
		}

		if(SDL_MUSTLOCK(screen)) 
			SDL_UnlockSurface(screen);


		file.close();
	}
	else
		std::cout << "Render aborted. File not saved." << std::endl;
}


Vector3f Render::traceRay(Ray &r)
{
	// Hitta den närmaste skärningspunkten med scenen
	Scene::ShootReturn rt = scene.shootRay(r);
	intersectionPoint = rt.getPoint();
	currentObject = rt.getObject();

	if (intersectionPoint != 0.0)
	{
		currentNormal = currentObject->getNormal(intersectionPoint).normalize();
		currentDir = (scene.getCameraPosition()-intersectionPoint).normalize();

		return computeRadiance();
	}
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
	Vector3f estimatedRadiance, lightDirection, nLightDirection, radiance;
	int nd = options->getNoShadowRays();

	Ray shadowRay;
	double x, z, xrand, zrand, pdf;

	std::tr1::shared_ptr<Light> light = scene.getLight(0);

	double lightArea = light->getWidth() * light->getHeight();
	Vector3f lightPos = light->getPosition();
	
	// Loopa över alla shadowrays
	for (int i = 0; i < nd; i++)
	{
		// Generera slumptal (Likformigt)
		xrand =  mc.getUniformNumber()*light->getWidth();
		zrand = mc.getUniformNumber()*light->getHeight();
		x = (lightPos.getX()  - light->getWidth()/2) + xrand;
		z = (lightPos.getZ() - light->getHeight()/2) + zrand;

		// Sätt rätt värden på shadow-rayen
		lightDirection = (Vector3f(x, lightPos.getY(), z) - intersectionPoint);
		shadowRay.setStart(intersectionPoint+0.01*lightDirection);
		shadowRay.setDirection(lightDirection);

		// Beräkna radiance
		pdf = mc.uniformPdf(xrand, 0, lightArea);

		estimatedRadiance += (light->getColor().mtimes(currentObject->getMaterial()->getColor()))*currentObject->getMaterial()->brdf(intersectionPoint, currentDir)
			* radianceTransfer(shadowRay, light->getNormal())/pdf;
	}

	// Normalisera med antalet shadowrays
	estimatedRadiance = estimatedRadiance/double(nd);

	return estimatedRadiance;
}


double Render::radianceTransfer(Ray &shadowRay, Vector3f lsNormal)
{
	// V(x,y) -- visibility function
	unsigned short int visible = 1;
	
	// Fixa längd och normaliserad vektor mellan lampa och punkten
	double rayLength = shadowRay.getDirection().squareNorm();
	Vector3f psiVector = shadowRay.getDirection();

	Vector3f p = scene.shootRay(shadowRay).getPoint();

	//if (shadowRay.getStart().getY() < -19.0 && shadowRay.getStart().getX() < 1.0)
	//std::cout << shadowRay.getStart() << ", " << shadowRay.getDirection() << std::endl;

	//std::cout << "lightLength: " << rayLength << ", hitLength: " << (p - shadowRay.getStart()).squareNorm() << std::endl;

	//std::cout << shadowRay.getStart() << ", " << shadowRay.getDirection() << std::endl;
	if (p != 0.0 && (p - shadowRay.getStart()).squareNorm() < rayLength)
	{
		visible = 0;
	}

	// G(x,y) -- geometry term
	double geometry = ((currentNormal * psiVector) * (lsNormal * -psiVector))/rayLength;

	//std::cout << geometry << std::endl;

	// V(x,y) * G(x,y)
	if (geometry >= 0.0)
		return geometry * visible;
	else
		return 0;
}
