#pragma once
#include<cmath>
#include<algorithm>
#include "Shape.h"
#include "Triangle.h"
class Tetrahedron :public Shape {
public:
	Tetrahedron(const VecPoint& a0, const VecPoint& a1, const VecPoint& a2, const VecPoint& a3) {
		this->a0 = a0;
		this->a1 = a1;
		this->a2 = a2;
		this->a3 = a3;
		color[0] = 0;
		color[1] = 0;
		color[2] = 255;
		tr[0] = { a0,a1,a2 };
		tr[1] = { a0,a1,a3 };
		tr[2] = { a0,a2,a3 };
		tr[3] = { a1,a2,a3 };
	}
	bool intersect(VecPoint ray_begin, VecPoint ray_direct, double& t, VecPoint& normal, double screen, double limit, VecPoint& intersection) override {
		int triang;
		double ttmp;
		double tmin = DBL_MAX;
		for (int i = 0; i < 4; i++) {
			if (tr[i].intersect(ray_begin, ray_direct, ttmp)) {
				if (ttmp < tmin) {
					tmin = ttmp;
					triang = i;
				}
			}
		}
		if (tmin >= limit) {
			return false;
		}
		normal.x = (tr[triang].p1 - tr[triang].p0).y * (tr[triang].p2 - tr[triang].p0).z - (tr[triang].p1 - tr[triang].p0).z * (tr[triang].p2 - tr[triang].p0).y;
		normal.y = (tr[triang].p1 - tr[triang].p0).z * (tr[triang].p2 - tr[triang].p0).x - (tr[triang].p1 - tr[triang].p0).x * (tr[triang].p2 - tr[triang].p0).z;
		normal.z = (tr[triang].p1 - tr[triang].p0).x * (tr[triang].p2 - tr[triang].p0).y - (tr[triang].p1 - tr[triang].p0).y * (tr[triang].p2 - tr[triang].p0).x;
		t = tmin;
		if (ray_direct * normal > 0) {
			normal = normal * (-1);
		}
		return true;
	}
private:
	Triangle tr[4];
	VecPoint a0;
	VecPoint a1;
	VecPoint a2;
	VecPoint a3;
};