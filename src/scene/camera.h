#ifndef CAMERA_H
#define CAMERA_H

namespace flaXx
{

class Camera
{
  public:
	explicit Camera(Vector3f, Vector3f, double);

	// Klassiska get-metoder
	Vector3f getDirection() { return direction; }
	Vector3f getPosition() { return position; }
	double focalDepth() { return focalDepth; }

  private:
	Vector3f direction;
	Vector3f position;
	double focalDepth;

};

} // end namespace flaXx
#endif // CAMERA_H
