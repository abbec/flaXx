#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "math/vector3f.h"

namespace flaXx
{

class ImagePlane
{
  public:

	ImagePlane(double, double, double);

	~ImagePlane() {}

	/* Få en koordinat för en pixel i bildplanet */
	Vector3f getPixelCoord(unsigned int x, unsigned int y);

  private:
	double fovx, fovy;
	unsigned int width, height;

};

} // end namespace flaXx
#endif // end IMAGEPLANE_H
