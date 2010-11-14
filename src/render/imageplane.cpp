#include "render/imageplane.h"

flaXx::ImagePlane::ImagePlane(double _fov, double width, double height) : fovx(_fov), width(width), height(height)
{
	pixels = new Uint32[width*height];
	
	// Räkna ut field of view för y
	fovy = (((double)height)/((double)width))*fovx*1.15;
}

Vector3f flaXx::ImagePlane::getPixelCoord(unsigned int x, unsigned int y)
{
	return Vector3f((((double)(2*x) - width)/(float)size.x)*tan(fovx),
					(((double)(2*y) - height)/(float)size.y)*tan(fovy), 1.0);
}


void setPixel(Uint32 value, unsigned int x, unsigned int y)
{
	Uint32 *pixmem = (Uint32*) pixels + x + y*width; 
	*pixmem = value;
}
