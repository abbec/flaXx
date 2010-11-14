#ifndef MATERIAL_H
#define MATERIAL_H

namespace flaXx
{

class Material
{
  public:
	virtual double brdf(const Vector3f &point, const Vector3f &dir) = 0;

	Vector3f getColor() { return color; }

  private:
	Vector3f color;

};

} // end namespace flaXx
#endif // end MATERIAL_H
