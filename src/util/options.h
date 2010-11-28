#ifndef OPTIONS_H
#define OPTIONS_H

#include <tr1/memory>
#include <string>

namespace flaXx
{

class Options
{

  public:
    Options() : width(640), height(480), noShadowRays(4), noHemisphereRays(2), noViewingRays(100) {}

    void setWidth(int w) { width = w; }
    int getWidth() { return width; }

	void setOutFileName(const std::string ofn) { outFileName = ofn; }
	std::string getOutFileName() { return outFileName; }

    void setHeight(int h) { height = h; }
    int getHeight() { return height; }

	unsigned int getNoShadowRays() { return noShadowRays; }

	unsigned int getNoHemisphereRays() { return noHemisphereRays; }

	unsigned int getNoViewingRays() { return noViewingRays; }

  private:
    unsigned int width;
    unsigned int height;

	std::string outFileName;

	unsigned int noShadowRays;
	unsigned int noHemisphereRays;
	unsigned int noViewingRays;
};

} // namespace flaXx

#endif
