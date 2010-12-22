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

#ifndef OPTIONS_H
#define OPTIONS_H

#ifdef WIN32
	#include <memory>
#else
	#include <tr1/memory>
#endif
#include <string>

namespace flaXx
{

class Options
{

  public:
    Options() : width(640), height(480), noShadowRays(4), noHemisphereRays(1), noViewingRays(10) {}

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
