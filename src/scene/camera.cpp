#include "scene/camera.h"

flaXx::Camera::Camera(Vector3f pos, Vector3f dir,
					  double fd = 10) : position(pos),
										direction(dir),
										focalDepth(fd)
{}


