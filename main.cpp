//#include"Box.h"
#include"Sphere.h"
#include"Shape.h"
#include"iostream"
#include<vector>
void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*> &objects);
int main() {
	std::cout << "Hello World!" << "\n";
	//Box box({3,-7,-6},{4,6,1});
	VecPoint cam = { 0,0,0 };
	VecPoint norm = { 1,0,0 };
	VecPoint up = { 0,0,1 };
	VecPoint light = { 2,2,0 };
	Sphere sphr(1, {0,0,0});
	std::vector<Shape*> obj;
    //obj.push_back(&box);
	obj.push_back(&sphr);
	render(cam, norm, up, 2.0, 20.0, 30.0, 640, 480, light, obj);
	return 0;
}
