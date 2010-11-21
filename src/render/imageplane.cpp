#include "render/imageplane.h"

flaXx::ImagePlane::ImagePlane(double _fov, double width, double height) : fovx(_fov), width(width), height(height)
{	
	// Räkna ut field of view för y
	fovy = (((double)height)/((double)width))*fovx*1.15;
}

flaXx::Vector3f flaXx::ImagePlane::getPixelCoord(unsigned int x, unsigned int y)
{
	return flaXx::Vector3f((((double)(2*x) - width)/(double)width)*tan(fovx),
					(-((double)(2*y) - height)/(double)height)*tan(fovy), 1.0);
}

