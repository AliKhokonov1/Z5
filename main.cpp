#include"Box.h"
#include"Sphere.h"
#include"Shape.h"
#include"iostream"
#include<vector>
void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*> &objects);
int main() {
	std::cout << "Hello World!" << "\n";
	Box box({3,-7,-6},{4,6,1});
	VecPoint cam = { 0,0,0 };
	VecPoint norm = { 1,0,0 };
	VecPoint up = { 0,0,1 };
	VecPoint light = { 0,-1,5 };
	Sphere sphr(0.5, {4,0,0});
	std::vector<Shape*> obj;
    obj.push_back(&box);
	obj.push_back(&sphr);
	render(cam, norm, up, 0.1, 10, 0.3, 1920, 1920, light, obj);
	return 0;
}
