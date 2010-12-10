/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
