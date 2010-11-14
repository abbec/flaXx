#ifndef DIFFUSE_H
#define DIFFUSE_H

namespace flaXx
{

class DiffuseMaterial : public Material
{
  public:

	DiffuseMaterial() : reflectance(0.5) {}
	DiffuseMaterial(double r) : reflectance(r) {}
	
	double getReflectance() { return reflectance; }
	void setReflectance(double r) { reflectance = r; }
	
	virtual float brdf(const Vector3f &point, const Vector3f &dir);

  private:
	double reflectance;

};


} // end namespace flaXx
#endif // end DIFFUSE_H
