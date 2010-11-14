#infdef LIGHT_H
#define LIGHT_H

namespace flaXx
{

class Light
{
  public:
	Light(Vector3f pos, Vector3f col) : position(pos), color(col) {}

	Vector3f getPosition() { return position; }
	Vector3f getColor() { return color; }

  private:
	Vector3f position;
	Vector3f color;
	
};



} // end namespace flaXx
#endif // end LIGHT_H
