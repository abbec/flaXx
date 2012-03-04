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

#include "render/imageplane.h"

flaXx::ImagePlane::ImagePlane(double _fov, unsigned int _width, unsigned int _height) : fovx(_fov), width(_width), height(_height), x1(-2), x2(2), y1(2), y2(-2), deviateAvailable(false)
{	
	// Calculate field of view
	//fovy = (((double)height)/((double)width))*fovx*1.15;
	double ratio = ((double)width)/((double)height);

	x1 *= ratio; x2 *=ratio;

	dx = (x2-x1)/double(width);
	dy = (y2-y1)/double(height);

	createTiles();
}

flaXx::Vector3f flaXx::ImagePlane::getPixelCoord(unsigned int x, unsigned int y) const
{
	return flaXx::Vector3f(x1 + x*dx, y1 + y*dy, 2.0);
}

unsigned int flaXx::ImagePlane::getTile()
{
	// Concentrate on the middle of the image first.
	// It is probably most important :)
	unsigned int middle = (unsigned int) floor(tiles.size()*0.5);
	unsigned int random = 0;
	if (tiles.size() > 2)
		random = (double(rand())/double(RAND_MAX)) > 0.5 ? 1 : -1;
		
	return middle+random;
}

void flaXx::ImagePlane::createTiles()
{
	double ratio = double(height)/double(width);
	unsigned int w = (unsigned int) ceil(width/10.0);
	unsigned int nTilesY = (unsigned int) ceil(10.0*ratio);
	unsigned int h = (unsigned int) ceil(height/(10.0*ratio));

	nTiles = 10*nTilesY;

	tiles.reserve(nTiles);

	unsigned int tempW = 0, tempH = 0;
	for (unsigned int x = 0; x < 10; x++)
	{
		for (unsigned int y = 0; y < nTilesY; y++)
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

