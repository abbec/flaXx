#ifndef RAY_H
#define RAY_H

namespace flaXx
{

class Ray
{
  public:
	
	Ray() : weight(1.0) {}

	Ray(Vector3f s, Vector3f d, Vector3f c, float w) : start(s),
													   direction(d), color(c), weight(w) {}

	Vector3f getStart() { return start; }
	void setStart(Vector3f s) { start = s; }
	
	Vector3f getDirection() { return direction; }
	void setDirection(Vector3f d) { direction = d; }
	
	Vector3f getColor() { return color; }
	void setColor(Vector3f c) { color = c; }

	double getWeight() { return weight; }
	void setWeight(double w) { weight = w; }

  private:
	Vector3f start;
	Vector3f direction;
	Vector3f color;
	double weight;
};

} // end namespace flaXx
#endif // end RAY_H
