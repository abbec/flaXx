#ifndef RAY_H
#define RAY_H

namespace flaXx
{

class Ray
{
  public:

	Ray() {}

	Ray(Vector3f s, Vector3f d) : start(s), direction(d) {}

	Vector3f getStart() const { return start; }
	void setStart(Vector3f s) { start = s; }
	
	Vector3f getDirection() const { return direction; }
	void setDirection(Vector3f d) { direction = d; }

  private:
	Vector3f start;
	Vector3f direction;
};

} // end namespace flaXx
#endif // end RAY_H
