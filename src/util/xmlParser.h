#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <list>
#include <vector>
#include <tr1/memory>

#include "scene/light.h"
#include "object/object.h"
#include "scene/camera.h"


namespace flaXx
{

class XMLParser
{

  public:
	explicit XMLParser(std::string fn): filename(fn),
										lights(new std::vector<std::tr1::shared_ptr<Light> >()), 
										objects(new std::list<std::tr1::shared_ptr<Object> >()) {}

	bool parse();

	std::tr1::shared_ptr<std::list<std::tr1::shared_ptr<Object> > > getObjects() { return objects; }
	std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<Light> > > getLights() { return lights; }
	std::tr1::shared_ptr<Camera> getCamera() { return camera; }

  private:

	std::string filename;
	std::tr1::shared_ptr<std::list<std::tr1::shared_ptr<Object> > > objects;
	std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<Light> > > lights;
	
	std::tr1::shared_ptr<Camera> camera;
	

};
} // end namespace flaXx
#endif // end XML_PARSER_H
