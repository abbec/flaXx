/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	/** Get a coordinate for a pixel in the view plane. */
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
