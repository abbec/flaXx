#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "render/render.h"

using namespace flaXx;

Render::Render() : complete(false), raylength(0)
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

			//std::cout << x << ", " << y << std::endl;

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

		for (int y = 0; y<options->getHeight(); y++)
		{
			for (int x = 0; x<options->getWidth(); x++)
			{

				pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;

				file.write(reinterpret_cast<char*>(pixmem32), 32);
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
	Vector3f dir = (scene.getCameraPosition()-intersectionPoint).normalize();

	if (intersectionPoint != 0.0)
		return computeRadiance(intersectionPoint, dir);
	else
		return Vector3f(0.0, 0.0, 0.0);
}

Vector3f Render::computeRadiance(Vector3f &x, Vector3f &dir)
{
	Vector3f estimatedRadiance;/* = currentObject->getMaterial()->getColor();*/
	
	//std::cout << "I computeRadiance" << std::endl;

	estimatedRadiance += directIllumination(x, dir);
	estimatedRadiance += indirectIllumination(x, dir);

	return estimatedRadiance;
}


Vector3f Render::directIllumination(Vector3f &x, Vector3f &theta)
{
	Vector3f estimatedRadiance, lightDirection, nLightDirection, radiance;
	int nd = options->getNoShadowRays();

	Ray shadowRay;
	double Lx, Lz, xrand, zrand, pdf;

	std::tr1::shared_ptr<Light> light = scene.getLight(0);

	double lightArea = light->getWidth() * light->getHeight();
	Vector3f lightPos = light->getPosition();

	MonteCarlo mc;
	mc.randomize();
	
	// Loopa över alla shadowrays
	for (int i = 0; i < nd; i++)
	{
		// Generera slumptal (Likformigt)
		xrand =  mc.getUniformNumber()*light->getWidth();
		zrand = mc.getUniformNumber()*light->getHeight();
		Lx = (lightPos.getX()  - light->getWidth()/2) + xrand;
		Lz = (lightPos.getZ() - light->getHeight()/2) + zrand;

		// Sätt rätt värden på shadow-rayen
		lightDirection = (Vector3f(Lx, lightPos.getY(), Lz) - x);
		shadowRay.setStart(x+0.01*lightDirection);
		shadowRay.setDirection(lightDirection);

		// Beräkna radiance
		pdf = mc.uniformPdf(xrand, 0, lightArea);

		estimatedRadiance += (light->getColor()).mtimes(currentObject->getMaterial()->brdf(x, theta, currentObject->getNormal(x), lightDirection))
			* radianceTransfer(shadowRay, light->getNormal(), x)/pdf;
	}

	// Normalisera med antalet shadowrays
	estimatedRadiance = estimatedRadiance/double(nd);

	return estimatedRadiance;
}


Vector3f Render::indirectIllumination(Vector3f &x, Vector3f &theta)
{
	Vector3f estimatedRadiance, rad;
	unsigned int nRays = options->getNoHemisphereRays();
	Ray sampledDir(intersectionPoint, Vector3f(0.0), Vector3f(1.0), 1.0/nRays);

	Vector3f y, psi, mpsi;

	float random, thetaN, phi, probability;

	Object *obj = currentObject.get();
	//std::cout << "Kolla: " << currentObject.get() << std::endl;

	MonteCarlo mc;
	mc.randomize();

	//std::cout << "Här uppe " << std::endl;

	double alpha = absorption();
	Vector3f Nx = obj->getNormal(x);
	double reflectance = (currentObject->getMaterial()->brdf(x, theta, Nx, Nx+theta*(Nx)).sum()/3.0);

	if (alpha < reflectance)
	{
		//raylength++;
		//std::cout << raylength << std::endl;
		//std::cout << "Här: efter if(!absorption())" << std::endl;
		for (int i = 0; i < nRays; i++)
		{

			float r1 = rand() / ((float)RAND_MAX + 1);
			phi = r1 * M_PI * 2.0;
			float r2 = rand() / ((float)RAND_MAX + 1);
			theta = acos(sqrt(r2));
			// theta = random * M_PI;
			float c = sqrt(1 - r2);
			probability = cos(thetaN) / M_PI;
			float xDir = cos(phi) * c;
			float yDir = sin(phi) * c;
			float zDir = sqrt(r2);

			//double xDir = (mc.getUniformNumber()*2.0)-1.0;
			//double yDir = (mc.getUniformNumber()*2.0)-1.0;
			//double zDir = (mc.getUniformNumber()*2.0)-1.0;

			sampledDir.setDirection((Vector3f(xDir, yDir, zDir)).normalize());
			sampledDir.setStart(x + sampledDir.getDirection()*0.01);

			psi = sampledDir.getDirection();
			mpsi = -psi;

			//std::cout << "Här nere" << i << std::endl;

			Scene::ShootReturn rt = scene.shootRay(sampledDir);
			y = rt.getPoint();

			//std::cout << "Efter: " << y << std::endl;

			// Se så att vi inte lämnar scenen
			if (y != 0.0)
			{

				currentObject = rt.getObject();
				sampledDir.setColor(currentObject->getMaterial()->getColor());

				//std::cout << "Current object: " << currentObject.get() << std::endl;

				rad = (computeRadiance(y, mpsi) * obj->getMaterial()->brdf(x, theta, Nx, psi)
					   *(Nx*psi))/mc.uniformPdf(xDir, 0 , 2.0*M_PI);

				estimatedRadiance += rad;
			}
			else
				return Vector3f(0.0);

		}
		
		estimatedRadiance = estimatedRadiance/nRays;

	}

	std::cout << estimatedRadiance/reflectance << std::endl;

	return estimatedRadiance/reflectance;

}


double Render::radianceTransfer(Ray &shadowRay, Vector3f lsNormal, Vector3f &x)
{
	// V(x,y) -- visibility function
	unsigned short int visible = 1;
	
	// Fixa längd och normaliserad vektor mellan lampa och punkten
	double rayLength = shadowRay.getDirection().squareNorm();
	Vector3f psiVector = shadowRay.getDirection();

	Vector3f p = scene.shootRay(shadowRay).getPoint();

	if (p != 0.0 && (p - shadowRay.getStart()).squareNorm() < rayLength)
	{
		visible = 0;
	}

	// G(x,y) -- geometry term
	double geometry = ((currentObject->getNormal(x) * psiVector) * (lsNormal * -psiVector))/rayLength;

	// V(x,y) * G(x,y)
	if (geometry >= 0.0)
		return geometry * visible;
	else
		return 0;
}

bool Render::absorption()
{

	MonteCarlo mc;
	mc.randomize();

	return mc.random();
}
