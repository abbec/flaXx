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
	// When we get an options object, we can create an image plane
	options = o;
	image = std::tr1::shared_ptr<ImagePlane>(new ImagePlane(M_PI/4.0, o->getWidth(), o->getHeight()));
}

void Render::render()
{
	std::cout << "Creating image plane.";

	// Create an SDL window to show rendering progress
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Event event;

	std::cout << ".";

	// Create SDL Surface
	screen = SDL_SetVideoMode(options->getWidth(),
							  options->getHeight(),
							  32, SDL_SWSURFACE);

	// Create a buffer surface for saving to file later.
	buffer = createBufferSurface();

	SDL_LockSurface(buffer);

	// Set window title and stuff
	SDL_WM_SetCaption("flaXx Monte-Carlo ray tracer", "flaXx");

	std::cout << ". Done!" << std::endl;

	std::cout << "Render started..." << std::endl;

	// Init random number generator
	srand((unsigned)time(0));

	// Initial values for rendering variables
	Uint32 finalColor = 0;
	Uint32 *pixmem32;
	Vector3f radiance;
	Vector3f pixelCoord, pixelWidth;

	unsigned int nRays = options->getNoViewingRays();
	unsigned int nRaysSqrt = ceil(sqrt(nRays));
	nRays = nRaysSqrt*nRaysSqrt;

	double pixWidth, pixHeight;

	for (int y = 0; y<options->getHeight(); y++)
	{
		for (int x = 0; x<options->getWidth(); x++)
		{
			// Lock screen before drawing pixel
			if(SDL_MUSTLOCK(screen))
			{
				if(SDL_LockSurface(screen) < 0)
					return;
			}

			radiance = 0.0;

			// Get pixel coordinates
			pixelCoord = image->getPixelCoord(x, y);
			pixelWidth = image->getPixelCoord(x+1, y+1) - pixelCoord;

			pixWidth = pixelWidth.getX()/double(nRaysSqrt);
			pixHeight = pixelWidth.getY()/double(nRaysSqrt);

			for (int i = 0; i < nRaysSqrt; i++)
			{
				for (int j = 0; j < nRaysSqrt; j++)
				{
					double jitterx = double(rand())/(double(RAND_MAX));
					double jittery = double(rand())/(double(RAND_MAX));

					double pixelX = pixelCoord.getX() + j*pixWidth*jitterx;
					double pixelY = pixelCoord.getY() + i*pixHeight*jittery;
					// Shoot a ray through the pixel and trace
					// it through the scene.*/
					Ray r(scene.getCameraPosition(), pixelCoord, Vector3f(1.0, 1.0, 1.0) ,1);
					radiance += traceRay(r);
				}
			}

			radiance = (radiance / nRays).colorNormalize();

			// Map Colors to a 32-bit word
			finalColor = SDL_MapRGB( screen->format, floor(radiance.getX()*255.0),
									 floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0));

			// Draw pixel on screen
			pixmem32 = (Uint32*) (screen->pixels) + (y*screen->pitch)/4 + x;
			*pixmem32 = finalColor;


			// Draw pixel in the back-buffer
			finalColor = SDL_MapRGBA( buffer->format, floor(radiance.getX()*255.0),
									  floor(radiance.getY()*255.0), floor(radiance.getZ()*255.0), SDL_ALPHA_OPAQUE );

			pixmem32 = (Uint32*) (buffer->pixels) + (y*buffer->pitch)/4 + x;
			*pixmem32 = finalColor;

			// Unlock the screen and update the pixel
			if(SDL_MUSTLOCK(screen))
				SDL_UnlockSurface(screen);

			SDL_UpdateRect(screen, x, y, 1, 1);


			// Poll an event so that it is possible to exit
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

	// Tell user that rendering is finshed
	std::cout << "Done! The rendering is finished. To exit and save the render, just close the window. " << std::endl;

	// Keep window open until the user wants to close
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

		FILE *fp;
		png_byte bit_depth = 8;
		png_bytep *row_pointers;
		png_structp png_ptr;
		int i, colortype;
		png_infop info_ptr;

		const char* filename = (options->getOutFileName()+".png").c_str();

		// (Re)lock the backbuffer
		if(SDL_MUSTLOCK(buffer))
		{
		 	if(SDL_LockSurface(buffer) < 0)
		 		return;
		}


		std::cout << "Saving to file: " << options->getOutFileName()+".png" << std::endl;

		/* Open output file */
		fp = fopen(filename, "wb");
		if (fp == NULL)
		{
			printf("fopen error");
		}

		/* Initializie png structures and callbacks */
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

		colortype = PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA;

		png_set_IHDR(png_ptr, info_ptr, buffer->w, buffer->h, 8,
					 colortype,
					 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
					 PNG_FILTER_TYPE_DEFAULT);

		/* Write image */
		png_write_info(png_ptr, info_ptr);
		png_set_packing(png_ptr);

		row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*buffer->h);
		for (i = 0; i < buffer->h; i++)
			row_pointers[i] = (png_bytep)(Uint8 *)buffer->pixels + i*buffer->pitch;

		png_write_image(png_ptr, row_pointers);
		png_write_end(png_ptr, info_ptr);

		/* Clean up */
		free(row_pointers);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);


		// Unlock the backbuffer
		if(SDL_MUSTLOCK(buffer))
			SDL_UnlockSurface(buffer);

	}
	else /* If rendering was aborted before it was finished */
		std::cout << "Render aborted. File not saved." << std::endl;
}


Vector3f Render::traceRay(Ray &r)
{
	// Find closest intersection with scene
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
	Vector3f estimatedRadiance;

	// Estimated radiance is the sum of direct and indirect components
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

	// Light is coming from the lightsource
	// and going towards the eye. Therefore
	// the direction has to be flipped.
	theta = -theta;

	// Fetch a light. TODO: Move inside loop and sample
	// among multiple lightsources
	std::tr1::shared_ptr<Light> light;

	double lightArea;
	int randLight;
	Vector3f lightPos;

	MonteCarlo mc;

	// Loop for all shadowrays
	for (int i = 0; i < nd; i++)
	{
		// Sample a lightsource uniformly
		randLight = floor(double(rand())/(double(RAND_MAX)+0.99)*scene.getNumLights());
		light = scene.getLight(randLight);

		lightArea = light->getWidth() * light->getHeight();
		lightPos = light->getPosition();

		// Generate point on lightsource (Uniform)
		xrand =  double(rand())/(double(RAND_MAX)+1)*light->getWidth();
		zrand =  double(rand())/(double(RAND_MAX)+1)*light->getHeight();
		Lx = (lightPos.getX()  - light->getWidth()/2) + xrand;
		Lz = (lightPos.getZ() - light->getHeight()/2) + zrand;

		// Set up the shadow ray
		lightDirection = (Vector3f(Lx, lightPos.getY(), Lz) - x);
		shadowRay.setStart(x+0.01*lightDirection);
		shadowRay.setDirection(lightDirection);

		// Calculate radiance
		pdf = mc.uniformPdf(xrand, 0, lightArea)*(1/double(scene.getNumLights()));

		estimatedRadiance += (light->getColor().mtimes(currentObject->getMaterial()->brdf(x, theta, currentObject->getNormal(x), lightDirection))) * radianceTransfer(shadowRay, light->getNormal(), x)/pdf;
	}

	// Normalize with the number of shadowrays
	estimatedRadiance = estimatedRadiance/double(nd);

	return estimatedRadiance;
}


Vector3f Render::indirectIllumination(Vector3f &x, Vector3f &theta)
{
	Vector3f estimatedRadiance(0.0), rad;
	unsigned int nRays = options->getNoHemisphereRays();

	Vector3f y, psi, mpsi;

	double thetaN, phi;

	MonteCarlo mc;

	// Use a local variable for the current object so
	// that we do not lose it in recursion
	std::tr1::shared_ptr<Object> obj = currentObject;

	// Russian roulette stopping condition
	double alpha = absorption();
	Vector3f Nx = obj->getNormal(x);
	double reflectance = (currentObject->getMaterial()->getSpecular() + currentObject->getMaterial()->getDiffuse())*0.5;

	if (alpha < reflectance)
	{
		// Generate N paths
		for (int i = 0; i < nRays; i++)
		{			

			// Generate point on hemisphere (cosine sampling)
			double r1 = double(rand()) / ((double)RAND_MAX);
			double phi = r1 * M_PI * 2.0;
			double r2 =  double(rand()) / (double(RAND_MAX));
			double r2sqrt = sqrt(r2);
			double thetaN = acos(r2sqrt);
			double c = sqrt(1-r2);

			double xDir = cos(phi) * c;
			double yDir = sin(phi) * c;
			double zDir = r2sqrt;

			psi = (Vector3f(xDir, yDir, zDir)+Nx).normalize();

			Ray sampledDir(x + psi*0.01, psi, Vector3f(1.0), 1.0/nRays);

			mpsi = -psi;

			Scene::ShootReturn rt = scene.shootRay(sampledDir);
			y = rt.getPoint();

			// Make sure we do not leave the scene
			if (y != 0.0)
			{
				// We are now at point y on a new object
				currentObject = rt.getObject();

				// Recursive evaluation of radiance
				estimatedRadiance += computeRadiance(y, mpsi).mtimes((obj->getMaterial()->brdf(x, theta, Nx, psi)));
			}

		}

		// Normalize with number of hemisphere rays
	estimatedRadiance = M_PI*estimatedRadiance/double(nRays);

	}

	// Normalize with the reflectance (1-absorption)
	return estimatedRadiance/(reflectance > 0.0 ? reflectance : 1.0);

}


double Render::radianceTransfer(Ray &shadowRay, Vector3f lsNormal, Vector3f &x)
{
	// V(x,y) -- visibility function
	unsigned short int visible = 1;

	// Fix a square length and a vector to the point
	double rayLength = shadowRay.getDirection().squareNorm();
	Vector3f psiVector = shadowRay.getDirection();

	Vector3f p = scene.shootRay(shadowRay).getPoint();

	// If the ray hits something on the way we have shadow
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
	// Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
	// for storing the image
    Uint32 rmask, gmask, bmask, amask;
	SDL_Surface *ret;

    /* SDL interprets each pixel as a 32-bit number, so the masks must depend
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

	return SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32,
								rmask, gmask, bmask, amask);
}

