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

#ifndef LIGHT_H
#define LIGHT_H

#include "math/vector3f.h"

namespace flaXx
{

class Light
{
  public:
	Light(Vector3f pos, Vector3f dir, Vector3f col, double w, double h) : position(pos),
																		  direction(dir),
																		  color(col), 
																		  width(w),
																		  height(h){}

	Vector3f getPosition() const { return position; }
	Vector3f getColor() const { return color; }

	double getHeight() const { return height; }
	double getWidth() const { return width; }

	Vector3f getNormal() const { return direction; }

  private:
	Vector3f position, direction;
	Vector3f color;
	double width, height;
	
};



} // end namespace flaXx
#endif // end LIGHT_H
