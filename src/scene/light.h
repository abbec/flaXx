#ifndef LIGHT_H
#define LIGHT_H

namespace flaXx
{

class Light
{
  public:
	Light(Vector3f pos, Vector3f dir, Vector3f col, double w, double h) : position(pos),
																		  direction(dir),
																		  color(col), 
																		  width(w),
																		  height(h){}

	Vector3f getPosition() const { return position; }
	Vector3f getColor() const { return color; }

	double getHeight() const { return height; }
	double getWidth() const { return width; }

	Vector3f getNormal() const { return direction; }

  private:
	Vector3f position, direction;
	Vector3f color;
	double width, height;
	
};



} // end namespace flaXx
#endif // end LIGHT_H
