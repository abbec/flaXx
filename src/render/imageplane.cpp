#include "render/imageplane.h"

flaXx::ImagePlane::ImagePlane(double _fov, unsigned int _width, unsigned int _height) : fovx(_fov), width(_width), height(_height), x1(-2), x2(2), y1(2), y2(-2)
{	
	// Räkna ut field of view för y
	//fovy = (((double)height)/((double)width))*fovx*1.15;
	double ratio = ((double)width)/((double)height);

	x1 *= ratio; x2 *=ratio;

	dx = (x2-x1)/double(width);
	dy = (y2-y1)/double(height);
}

flaXx::Vector3f flaXx::ImagePlane::getPixelCoord(unsigned int x, unsigned int y) const
{
	return flaXx::Vector3f(x1 + x*dx, y1 + y*dy, 2.5);
}

