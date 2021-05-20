#pragma once
#include<cmath>
#include<algorithm>
#include "Shape.h"
class Box :public Shape {
public:
	Box(const VecPoint& min, const VecPoint& max) {
		this->min = min;
		this->max = max;
		color[0] = 0;
		color[1] = 255;
		color[2] = 0;
	}
	bool intersect(VecPoint ray_begin, VecPoint ray_direct, VecPoint& normal, double& t) override {
		double t_near = DBL_MIN;
		double t_far = DBL_MAX;
		double t1, t2;
		double eps = 1e-10;
		VecPoint N;
		for (int i = 0; i < 3; i++){
			if (fabs(ray_direct[i]) >= eps) {
				t1 = (min[i] - ray_begin[i]) / ray_direct[i];
				t2 = (max[i] - ray_begin[i]) / ray_direct[i];
				if (t1 > t2) {
					std::swap(t1, t2);
				}
				if (t1 > t_near) {
					t_near = t1;
					if (i == 0) {
						N.x = 1;
						N.y = 0;
						N.z = 0;
					}
					else if (i == 1) {
						N.x = 0;
						N.y = 1;
						N.z = 0;
					}
					else if (i == 2) {
						N.x = 0;
						N.y = 0;
						N.z = 1;
					}
				}
				if (t2 < t_far) {
					t_far = t2;
				}
				if (t_near > t_far) {
					return false;
				}
				if (t_far < 0.0) {
					return false;
				}
			}
			//
		}
		if (t_near <= t_far && t_far >= 0) {
			normal = N;
			if (((ray_direct.x * normal.x) + (ray_direct.y * normal.y) + (ray_direct.z * normal.z)) > 0) {
				normal = normal * (-1);
			}
			return true;
		}
		else {
			return false;
		}
	}
private:
	VecPoint min;
	VecPoint max;
};