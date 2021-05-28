#pragma once
#include<cmath>
#include<algorithm>
#include "Shape.h"
class Sphere :public Shape {
public:
	Sphere(double rad, VecPoint centre) :radius(rad) {
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
		this->centre = centre;
	}
	bool intersect(VecPoint ray_begin, VecPoint ray_direct, double& t, VecPoint& normal, double screen, double limit) override {
		double a = ray_direct * ray_direct;
		double b = ray_direct * (ray_begin - centre);
		double c = (ray_begin - centre) * (ray_begin - centre) - radius * radius;
		double d = b * b - a * c;
		double t1, t2;
		if (d < 0) {
			return false;
		}
		t1 = (-b - std::sqrt(d)) / a;
		t2 = (-b + std::sqrt(d)) / a;

		if (t1 > t2) {
			std::swap(t1, t2);
		}
		if (t1 > limit) {
			return false;
		}
		if (t2 < screen) {
			return false;
		}
		if (t1 < screen) {
			t1 = t2;
		}
		t = t1;
		normal = ray_begin + ray_direct * t - centre;
		normal = (normal) * (1 / normal.lenght());
		if (ray_direct * (normal) > 0) {
			(normal) = (normal) * (-1);
		}
		return true;
	}
private:
	double radius;
};