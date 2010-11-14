#ifndef OBJECT_H
#define OBJECT_H

#include <tr1/memory>

namespace flaXx
{

class Object
{
  public:
	Object(std::tr1::shared_ptr<Material> m) : material(m){}

	virtual ~Object(){}

	virtual Vector3f intersect(Ray &ray) = 0;
	virtual Vector3f getNormal(Vector3f &point) = 0;

  private:
	std::tr1::shared_ptr<Material> material;

};

} // end namespace flaXx
#endif // end OBJECT_H
