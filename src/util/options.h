#ifndef OPTIONS_H
#define OPTIONS_H

namespace flaXx
{

class Options
{

  public:
    Options() : width(1024), height(768);

    void setWidth(int w){ width = w;}
    int getWidth(){ return width; }

    void setHeight(int h){ height = h;}
    int getHeight(){ return height; }

  private:
    unsigned int width;
    unsigned int height;

};

}
