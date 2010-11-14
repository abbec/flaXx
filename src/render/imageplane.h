#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "SDL.h"

namespace flaXx
{

class ImagePlane
{
  public:

	ImagePlane(double, double, double);

	/* Få en koordinat för en pixel i bildplanet */
	Vector3f getPixelCoord(unsigned int x, unsigned int y);

	/* Sätter ett värde på en pixel i bildplanet */
	void setPixel(Uint32 value, unsigned int x, unsigned int y);

  private:
	pixels *Uint32;
	double fovx, fovy;
	unsigned int widht, height;

}

} // end namespace flaXx
#endif // end IMAGEPLANE_H
