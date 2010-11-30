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
