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

#ifndef CAMERA_H
#define CAMERA_H

#include "math/vector3f.h"

namespace flaXx
{

class Camera
{
  public:
	explicit Camera(Vector3f, Vector3f, double);

	Vector3f getDirection() { return direction; }
	Vector3f getPosition() { return position; }
	double getFocalDepth() { return focalDepth; }

  private:
	Vector3f direction;
	Vector3f position;
	double focalDepth;

};

} // end namespace flaXx
#endif // CAMERA_H
