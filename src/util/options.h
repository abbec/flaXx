#ifndef OPTIONS_H
#define OPTIONS_H

#include <tr1/memory>
#include <string>

namespace flaXx
{

class Options
{

  public:
    Options() : width(320), height(240), noShadowRays(36) {}

    void setWidth(int w) { width = w; }
    int getWidth() { return width; }

	void setOutFileName(const std::string ofn) { outFileName = ofn; }
	std::string getOutFileName() { return outFileName; }

    void setHeight(int h) { height = h; }
    int getHeight() { return height; }

	unsigned int getNoShadowRays() { return noShadowRays; }

  private:
    unsigned int width;
    unsigned int height;

	std::string outFileName;

	unsigned int noShadowRays;

};

} // namespace flaXx

#endif
