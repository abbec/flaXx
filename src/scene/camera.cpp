#include "scene/camera.h"


flaXx::Camera::Camera(flaXx::Vector3f pos, flaXx::Vector3f dir,
					  double fd = 10) : position(pos),
										direction(dir),
										focalDepth(fd)
{}


