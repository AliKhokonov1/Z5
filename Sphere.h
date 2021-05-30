#pragma once
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Shape.h"
class Sphere :public Shape {
public:
	Sphere(double rad, VecPoint centre) :radius(rad) {
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
		this->centre = centre;
	}
	bool intersect(VecPoint ray_begin, VecPoint ray_direct, double& t, VecPoint& normal, double screen, double limit, VecPoint& intersection) override {
		double coef_a = pow(ray_direct[0], 2) + pow(ray_direct[1], 2) + pow(ray_direct[2], 2);
		double coef_b = 2 * (ray_begin[0] * ray_direct[0] + ray_begin[1] * ray_direct[1] +
			ray_begin[2] * ray_direct[2] - ray_direct[0] * centre[0] - ray_direct[1] * centre[1] - ray_direct[2] * centre[2]);
		double coef_c = pow(ray_begin[0] - centre[0], 2) + pow(ray_begin[1] - centre[1], 2) + pow(ray_begin[2] - centre[2], 2) - pow(radius, 2);
		double discriminant = pow(coef_b, 2) - 4 * coef_a * coef_c;
		double t1, t2;
		if (discriminant <= 0) {
			return false;
		}
		t1 = (-coef_b - std::sqrt(discriminant)) / (2 * coef_a);
		t2 = (-coef_b + std::sqrt(discriminant)) / (2 * coef_a);

		if (t1 > t2) {
			std::swap(t1, t2);
		}
		t = t1;
		if (t1 < 0) {
			t = t2;
		}
		intersection = ray_begin + ray_direct * t;
		normal = (intersection - centre);
		normal = (normal) * (1 / normal.lenght());
		if (ray_direct * normal > 0) {
			normal = normal * (-1);
		}
		return true;
	}
private:
	double radius;
};
