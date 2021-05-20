#pragma once
#include "VecPoint.h"

class Shape{
public:
	virtual bool intersect(VecPoint ray_begin, VecPoint ray_direct, VecPoint& normal, double& t) = 0;//Определяет пересечение или не пересечение
	unsigned char color[3];
	VecPoint centre;
};