#pragma once
struct VecPoint {
	double x;
	double y;
	double z;
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
	VecPoint operator*(double f){
		VecPoint s;
		s.x = f*x;
		s.y = f*y;
		s.z = f*z;
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
		s.x = f.x - x;
		s.y = f.y - y;
		s.z = f.z - z;
		return s;
	}

};

