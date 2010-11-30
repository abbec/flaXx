#include "render/imageplane.h"

flaXx::ImagePlane::ImagePlane(double _fov, unsigned int _width, unsigned int _height) : fovx(_fov), width(_width), height(_height), x1(-2), x2(2), y1(2), y2(-2), deviateAvailable(false)
{	
	// Räkna ut field of view för y
	//fovy = (((double)height)/((double)width))*fovx*1.15;
	double ratio = ((double)width)/((double)height);

	x1 *= ratio; x2 *=ratio;

	dx = (x2-x1)/double(width);
	dy = (y2-y1)/double(height);

	createTiles();
}

flaXx::Vector3f flaXx::ImagePlane::getPixelCoord(unsigned int x, unsigned int y) const
{
	return flaXx::Vector3f(x1 + x*dx, y1 + y*dy, 2.5);
}

unsigned int flaXx::ImagePlane::getTile()
{
	// Concentrate on the middle of the image first.
	// It is probably most important :)
	unsigned int middle = floor(tiles.size()*0.5);
	unsigned int random = (double(rand())/double(RAND_MAX)) > 0.5 ? 1 : -1;

	return middle+random;
}

void flaXx::ImagePlane::createTiles()
{
	double ratio = double(height)/double(width);
	unsigned int w = ceil(width/10.0);
	unsigned int nTilesY = ceil(10.0*ratio);
	unsigned int h = ceil(height/(10.0*ratio));

	nTiles = 10*nTilesY;

	tiles.reserve(nTiles);

	unsigned int tempW = 0, tempH = 0;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < nTilesY; y++)
		{
			tempW = w; tempH = h;
			
			if (x == 9)
				tempW = width - x*tempW;
			if (y == (nTilesY-1))
				tempH = height - y*tempH;

			tiles.push_back(Tile(x*w, y*h, tempW, tempH));
		}
	}
}

