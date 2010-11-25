#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "render/render.h"
#include <png.h>

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
							  32, SDL_SWSURFACE);

	buffer = createBufferSurface();

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
									  floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0));

			// Rita pixeln på skärmen
			pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;
			*pixmem32 = finalColor;


			// Rita pixeln i minnet
			finalColor = SDL_MapRGBA( buffer->format, floor(radiance.getX()*255.0), 
									  floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0), SDL_ALPHA_OPAQUE );

			pixmem32 = (Uint32*) (buffer->pixels) + (y*buffer->pitch)/4 + x;
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


static int png_colortype_from_surface(SDL_Surface *surface)
{
	int colortype = PNG_COLOR_MASK_COLOR; /* grayscale not supported */

	if (surface->format->palette)
		colortype |= PNG_COLOR_MASK_PALETTE;
	else if (surface->format->Amask)	
		colortype |= PNG_COLOR_MASK_ALPHA;

	printf("Amask: %d\n", surface->format->Amask);
		
	return colortype;
}

void Render::saveToFile()
{

	if (complete)
	{

		FILE *fp;
		png_byte bit_depth = 8;
		png_bytep *row_pointers;
		png_structp png_ptr;
		int i, colortype;
		png_infop info_ptr;
		const char* filename = (options->getOutFileName()+".png").c_str();

		// Lås skärmen innan vi ritar upp pixeln
		if(SDL_MUSTLOCK(buffer)) 
		 {
		 	if(SDL_LockSurface(buffer) < 0) 
		 		return;
		 }


		std::cout << "Saving to file: " << options->getOutFileName()+".png" << std::endl;

		/*Uint32 *pixmem32;

		png::image< png::rgba_pixel<Uint8> > image(options->getWidth(), options->getHeight());
		 for (size_t y = 0; y < image.get_height(); ++y)
		 {
			 for (size_t x = 0; x < image.get_width(); ++x)
			 {
				 pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;

				 image.set_pixel(x, y, *pixmem32);
				 // non-checking equivalent of image.set_pixel(x, y, ...);
			 }
		 }
		 image.write("rgb.png");*/
		
		/* Opening output file */
		fp = fopen(filename, "wb");
		if (fp == NULL) 
		{
			printf("fopen error");
		}

		/* Initializing png structures and callbacks */
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
										  NULL, NULL, 
										  NULL);
		if (png_ptr == NULL) 
		{
			printf("png_create_write_struct error!\n");
		}

		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL) 
		{
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			printf("png_create_info_struct error!\n");
		}

		if (setjmp(png_jmpbuf(png_ptr))) 
		{
			png_destroy_write_struct(&png_ptr, &info_ptr);
			fclose(fp);
		}

		png_init_io(png_ptr, fp);

		colortype = png_colortype_from_surface(buffer);

		png_set_IHDR(png_ptr, info_ptr, buffer->w, buffer->h, 8, 
				 colortype,	
				 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
				 PNG_FILTER_TYPE_DEFAULT);

		/* Writing the image */
		png_write_info(png_ptr, info_ptr);
		png_set_packing(png_ptr);

		row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*buffer->h);
		for (i = 0; i < buffer->h; i++)
			row_pointers[i] = (png_bytep)(Uint8 *)buffer->pixels + i*buffer->pitch;

		png_write_image(png_ptr, row_pointers);
		png_write_end(png_ptr, info_ptr);

		/* Cleaning out... */
		free(row_pointers);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);



		if(SDL_MUSTLOCK(buffer)) 
			SDL_UnlockSurface(buffer);

	}
	else
		std::cout << "Render aborted. File not saved." << std::endl;
}


Vector3f Render::traceRay(Ray &r)
{
	// Hitta den närmaste skärningspunkten med scenen
	Scene::ShootReturn rt = scene.shootRay(r);
	Vector3f x = rt.getPoint();
	currentObject = rt.getObject();
	Vector3f dir = (x - scene.getCameraPosition()).normalize();

	if (x != 0.0)
		return computeRadiance(x, dir);
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
	Vector3f estimatedRadiance(0.0), rad;
	unsigned int nRays = options->getNoHemisphereRays();

	Vector3f y, psi, mpsi;

	float random, thetaN, phi, probability;

	std::tr1::shared_ptr<Object> obj = currentObject;
	double alpha = absorption();
	Vector3f Nx = obj->getNormal(x);
	double reflectance = (currentObject->getMaterial()->getSpecular() + currentObject->getMaterial()->getDiffuse())*0.5;

	if (alpha < reflectance)
	{
		//raylength++;
		//std::cout << "  Inne" << std::endl;
		//std::cout << "Här: efter if(!absorption())" << std::endl;
		for (int i = 0; i < nRays; i++)
		{

			float r1 = rand() / ((float)RAND_MAX + 1);
			phi = r1 * M_PI * 2.0;
			float r2 = rand() / ((float)RAND_MAX + 1);
			thetaN = acos(sqrt(r2));
			// theta = random * M_PI;
			float c = sqrt(1 - r2);
			probability = cos(thetaN) / M_PI;
			float xDir = cos(phi) * c;
			float yDir = sin(phi) * c;
			float zDir = sqrt(r2);

			//double xDir = (mc.getUniformNumber()*2.0)-1.0;
			//double yDir = (mc.getUniformNumber()*2.0)-1.0;
			//double zDir = (mc.getUniformNumber()*2.0)-1.0;

			psi = (Vector3f(xDir, yDir, zDir) + Nx).normalize();

			//std::cout << x << ", " << psi << std::endl;

			Ray sampledDir(x + psi*0.01, psi, Vector3f(1.0), 1.0/nRays);

			mpsi = -psi;


			//std::cout << "Här nere" << i << std::endl;

			Scene::ShootReturn rt = scene.shootRay(sampledDir);
			y = rt.getPoint();

			//std::cout << "Efter: " << y << std::endl;

			// Se så att vi inte lämnar scenen
			if (y != 0.0)
			{

				currentObject = rt.getObject();
				//sampledDir.setColor(currentObject->getMaterial()->getColor());

				//std::cout <<  obj->getMaterial()->brdf(x, theta, Nx, psi) << std::endl;

				rad = (computeRadiance(y, mpsi) * obj->getMaterial()->brdf(x, theta, Nx, psi)
					   *(Nx*psi))/(1/2.0*M_PI);

				//std::cout << rad << std::endl;

				estimatedRadiance += rad;
			}

		}
		
		estimatedRadiance = estimatedRadiance/double(nRays);

	}

	//if (estimatedRadiance != 0.0)
	//std::cout << "Stopping recursion..." << std::endl;

	return estimatedRadiance/(reflectance > 0.0 ? reflectance : 1.0);

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

double Render::absorption()
{
	return double(rand())/(double(RAND_MAX)+1);
}

SDL_Surface *Render::createBufferSurface()
{
/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;
	SDL_Surface *ret;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    ret = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32,
								rmask, gmask, bmask, amask);

	return ret;
}

