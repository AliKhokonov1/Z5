#pragma once
#include<cmath>
#include<algorithm>
#include "Shape.h"
class Triangle
{
public:
    VecPoint p0;
    VecPoint p1;
    VecPoint p2;
    Triangle() = default;
    Triangle(VecPoint p0, VecPoint p1, VecPoint p2) {
        this->p0 = p0;
        this->p1 = p1;
        this->p2 = p2;
    }
    bool intersect(VecPoint ray_begin, VecPoint ray_direct, double& t) {//Пересечение треугольника и луча
        double u, v, det, dett, detu, detv;
        double eps = 1e-10;
        VecPoint d = ray_direct;
        VecPoint b = ray_begin;
        det = d.x * (p0 - p1).y * (p0 - p2).z + (p0 - p1).x * (p0 - p2).y * d.z + (p0 - p2).x * d.y * (p0 - p1).z - (p0 - p2).x * (p0 - p1).y * d.z - (p0 - p1).x * d.y * (p0 - p2).z - d.x * (p0 - p2).y * (p0 - p1).z;
        dett = (p0 - b).x * (p0 - p1).y * (p0 - p2).z + (p0 - p1).x * (p0 - p2).y * (p0 - b).z + (p0 - p2).x * (p0 - b).y * (p0 - p1).z - (p0 - p2).x * (p0 - p1).y * (p0 - b).z - (p0 - p1).x * (p0 - b).y * (p0 - p2).z - (p0 - b).x * (p0 - p2).y * (p0 - p1).z;
        detu = d.x * (p0 - b).y * (p0 - p2).z + (p0 - b).x * (p0 - p2).y * d.z + (p0 - p2).x * d.y * (p0 - b).z - (p0 - p2).x * (p0 - b).y * d.z - (p0 - b).x * d.y * (p0 - p2).z - d.x * (p0 - p2).y * (p0 - b).z;
        detv = d.x * (p0 - p1).y * (p0 - b).z + (p0 - p1).x * (p0 - b).y * d.z + (p0 - b).x * d.y * (p0 - p1).z - (p0 - b).x * (p0 - p1).y * d.z - (p0 - p1).x * d.y * (p0 - b).z - d.x * (p0 - b).y * (p0 - p1).z;
        if (det < eps) {
            return false;
        }
        u = detu / det;
        if (u < 0.0 || u > 1.0) {
            return false;
        }
        v = detv / det;
        if (v < 0.0 || u + v > 1.0) {
            return false;
        }
        t = dett / det;
        return true;
    }
};
