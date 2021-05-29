#pragma once
#include "VecPoint.h"

class Shape {
public:
	virtual bool intersect(VecPoint ray_begin, VecPoint ray_direct, double& t, VecPoint& normal, double screen, double limit, VecPoint& intersection) = 0;
	unsigned char color[3];
	VecPoint centre;
};
