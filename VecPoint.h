#pragma once
#include<cmath>
#include<vector>
struct VecPoint {
	double x = 0;
	double y = 0;
	double z = 0;
	double& operator[](int i) {
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}
	VecPoint operator*(double f) {
		VecPoint s;
		s.x = f * x;
		s.y = f * y;
		s.z = f * z;
		return s;
	}
	VecPoint operator+(const VecPoint& f) {
		VecPoint s;
		s.x = f.x + x;
		s.y = f.y + y;
		s.z = f.z + z;
		return s;
	}
	VecPoint operator-(const VecPoint& f) {
		VecPoint s;
		s.x = x - f.x;
		s.y = y - f.y;
		s.z = z - f.z;
		return s;
	}
	double lenght() {
		return std::sqrt(x * x + y * y + z * z);
	}
	double operator*(const VecPoint& a) {
		return (x * a.x) + (y * a.y) + (z * a.z);
	}
};
