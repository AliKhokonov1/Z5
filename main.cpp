#include "Box.h"
#include "Sphere.h"
#include "Shape.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "iostream"

#include <vector>

void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*>& objects);

int main() {
	std::cout << "Hello World!" << "\n";
	Box box({200,200,200},{300,300,300});
	VecPoint cam = { 0,0,0 };
	VecPoint norm = { 1,0,0 };
	VecPoint up = { 0,0,1 };
	VecPoint light = { 120,30,50 };
	Sphere sphr(100, { 600,0,0 });
	Tetrahedron tetr({ 200,50,100}, { 300,50,200}, {300,150,100}, { 300,100,100});
	std::vector<Shape*> obj;
	obj.push_back(&box);
	obj.push_back(&sphr);
	obj.push_back(&tetr);
	render(cam, norm, up, 150.0, 2000.0, 1.5, 640, 480, light, obj);
	return 0;
}
