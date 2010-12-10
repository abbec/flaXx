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

#ifndef TILE_H
#define TILE_H

namespace flaXx
{
/** Class representing a tile in the image.
 */
class Tile
{
  public:
	explicit Tile(unsigned int _x, unsigned int _y, unsigned int _w, unsigned int _h) :
		x(_x), y(_y), w(_w), h(_h) {}

	unsigned int getX() { return x; }
	unsigned int getY() { return y; }
	unsigned int getWidth() { return w; }
	unsigned int getHeight() { return h; }

  private:
	unsigned int x, y;
	unsigned int w, h;
};

} // end namespace flaXx
#endif
