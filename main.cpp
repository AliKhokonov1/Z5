#include "Box.h"
#include "Sphere.h"
#include "Shape.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*>& objects);
int main() {
	std::cout << "Hello World!" << "\n";
	ifstream fin("objects.txt");
	if (fin.fail()) {
		cout << "File did not open!" << endl;
		return 1;
	}
	string str;
	string type;
	std::vector<Shape*> obj;
	while (getline(fin, str)) {
		stringstream w(str);
		w >> type;
		if (type == "box") {
			VecPoint min, max;
			w >> min.x >> min.y >> min.z >> max.x >> max.y >> max.z;
			obj.push_back(new Box(min, max));
		}
		else if (type == "sphr") {
			VecPoint centre;
			double radius;
			w >> radius >> centre.x >> centre.y >> centre.z;
			obj.push_back(new Sphere(radius, centre));
		}
		else if (type == "tetr") {
			VecPoint t0, t1, t2, t3;
			w >> t0.x >> t0.y >> t0.z >> t1.x >> t1.y >> t1.z >> t2.x >> t2.y >> t2.z >> t3.x >> t3.y >> t3.z;
			obj.push_back(new Tetrahedron(t0, t1, t2, t3));
		}
	}
	ifstream fon("parametrs.txt");
	if (fon.fail()) {
		cout << "File did not open!" << endl;
		return 1;
	}
	VecPoint cam,normal,up,light;
	double screen, limit, alpha, width, height;
	while (getline(fon, str)) {
		stringstream w(str);
		w >> type;
		if (type == "cam") {
			w >> cam.x >> cam.y >> cam.z;
		}
		else if (type == "normal") {
			w >> normal.x >> normal.y >> normal.z;
		}
		else if (type == "up") {
			w >> up.x >> up.y >> up.z;
		}
		else if (type == "light") {
			w >> light.x >> light.y >> light.z;
		}
		else if (type == "screen") {
			w >> screen;
		}
		else if (type == "limit") {
			w >> limit;
		}
		else if (type == "alpha") {
			w >> alpha;
		}
		else if (type == "width") {
			w >> width;
		}
		else if (type == "height") {
			w >> height;
		}
	}
	render(cam, normal, up, screen, limit, alpha, width, height, light, obj);
	for (int i = 0; i < obj.size(); i++) { delete obj[i];}
	fin.close();
	fon.close();
	return 0;
}
