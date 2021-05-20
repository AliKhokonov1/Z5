#pragma once
#include<cmath>
#include<algorithm>
#include "Shape.h"
class Sphere :public Shape {
public:
	Sphere(double rad, VecPoint centre):radius(rad){
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
		this->centre = centre;
	}
	bool intersect(VecPoint ray_begin, VecPoint ray_direct, VecPoint& normal, double& t) override{
		double a = ray_direct.x*ray_direct.x+ray_direct.y*ray_direct.y+ray_direct.z*ray_direct.z;
		double b = ray_direct.x * (ray_begin - centre).x + ray_direct.y * (ray_begin - centre).y + ray_direct.z * (ray_begin - centre).z;
		double c = (ray_begin - centre).x * (ray_begin - centre).x + (ray_begin - centre).y * (ray_begin - centre).y + (ray_begin - centre).z * (ray_begin - centre).z - radius * radius;
		double d = b * b - a * c;
		double t1, t2;
		if (d < 0) {
			return false;
		}
		t1 = (-b - sqrt(d)) / a;
		t2 = (-b + sqrt(d)) / a;
		if (t1 > t2) {
			std::swap(t1, t2);
		}
		t = t1;
		normal = ray_begin + ray_direct * t - centre;
		if (((ray_direct.x * normal.x) + (ray_direct.y * normal.y) + (ray_direct.z * normal.z)) > 0) {
			normal = normal * (-1);
		}
		return true;
	}
private:
	double radius;
};