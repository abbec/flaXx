#ifndef OPTIONS_H
#define OPTIONS_H

#include <tr1/memory>

namespace flaXx
{

class Options
{

  public:
    Options() : width(1024), height(768), noShadowRays(36) {}

    void setWidth(int w) { width = w; }
    int getWidth() { return width; }

    void setHeight(int h) { height = h; }
    int getHeight() { return height; }

	unsigned int getNoShadowRays() { return noShadowRays; }

  private:
    unsigned int width;
    unsigned int height;

	unsigned int noShadowRays;

};

} // namespace flaXx

#endif
