#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include <cstdlib>
#include <vector>
#include "math/vector3f.h"
#include "render/tile.h"

namespace flaXx
{

class ImagePlane
{
  public:

	ImagePlane(double, unsigned int, unsigned int);

	~ImagePlane() {}

	bool isFinished() { return tiles.empty(); }
	void setFinished(unsigned int tileNum) { tiles.erase(tiles.begin() + tileNum); }

	unsigned int getTile();

	unsigned int getTileWidth(const unsigned int tileNum) { return tiles.at(tileNum).getWidth(); }
	unsigned int getTileHeight(const unsigned int tileNum) { return tiles.at(tileNum).getHeight(); }

	unsigned int getTileX(const unsigned int tileNum) { return tiles.at(tileNum).getX(); }
	unsigned int getTileY(const unsigned int tileNum) { return tiles.at(tileNum).getY(); }

	/** Få en koordinat för en pixel i bildplanet */
	Vector3f getPixelCoord(unsigned int x, unsigned int y) const;

  private:
	double fovx, fovy;
	unsigned int width, height;
	double dx, dy, x1, x2, y1, y2;
	std::vector<Tile> tiles;

	bool deviateAvailable;
	double storedDeviate;
	
	unsigned int nTiles;
	
	void createTiles();
};

} // end namespace flaXx
#endif // end IMAGEPLANE_H
