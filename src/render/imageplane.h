#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "math/vector3f.h"

namespace flaXx
{

class ImagePlane
{
  public:

	ImagePlane(double, unsigned int, unsigned int);

	~ImagePlane() {}

	/* Få en koordinat för en pixel i bildplanet */
	Vector3f getPixelCoord(unsigned int x, unsigned int y) const;

  private:
	double fovx, fovy;
	unsigned int width, height;
	double dx, dy, x1, x2, y1, y2;

};

} // end namespace flaXx
#endif // end IMAGEPLANE_H
