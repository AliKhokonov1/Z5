
#include "VecPoint.h"
#include "Shape.h"
#include "CImg.h" 

#include <vector>
#include <iostream>
#include <chrono>

double distance(VecPoint v1, VecPoint v2) // Distance between two points
{
	return sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2) + pow((v1.z - v2.z), 2));
}

void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*>& objects) {
	VecPoint sideways, start;
	double screen_height = height;
	double screen_width = width;
	normal = normal * (1 / normal.lenght());
	up = up * (1 / up.lenght());
	sideways.x = up.y * normal.z - up.z * normal.y;
	sideways.y = up.z * normal.x - up.x * normal.z;
	sideways.z = up.x * normal.y - up.y * normal.x;

	start = normal * screen + up * (screen_height / 2) + sideways * (screen_width / 2);


	using namespace cimg_library;

	CImg<unsigned char> image(width, height, 1, 3, 0);
	VecPoint Ntmp, N, L;
	VecPoint ray_begin = cam;
	VecPoint ray_direction;
	Shape* obj = nullptr;
	double t, tmin = std::numeric_limits<double>::max();
	double ambient[3];
	double diffuse[3];
	double color[3];
	double NL;

	VecPoint row_start = start;
	VecPoint curr_point;

	for (int j = 0; j < height; j++) {
		curr_point = row_start;
		for (int i = 0; i < width; i++) {

			ray_direction = curr_point - cam;
			ray_direction = ray_direction * (1 / screen);

			tmin = DBL_MAX;
			VecPoint interTmp;
			VecPoint intersection;
			obj = nullptr;
			for (int k = 0; k < objects.size(); k++) {

				if (objects[k]->intersect(ray_begin, ray_direction, t, Ntmp, screen, limit, interTmp)) {
					if (t<tmin && t > screen) {
						N = Ntmp;
						tmin = t;
						obj = objects[k];
						intersection = interTmp;
					}
				}
			}
			if (tmin >= limit) {
				image(i, j, 0) = 0;
				image(i, j, 1) = 0;
				image(i, j, 2) = 0;
			}
			else {
				N = N * (1 / N.lenght());
				L = (light - (ray_direction * tmin + ray_begin));
				L = L * (1 / L.lenght());
				NL = N * L;
				if (NL < 0) {
					NL = 0.0;
				}
				for (int k = 0; k < 3; k++) {
					ambient[k] = (0.2 * (obj->color[k]));
				}
				for (int k = 0; k < 3; k++) {
					diffuse[k] = (0.8 * NL * (obj->color[k]));
				}
				for (int k = 0; k < 3; k++) {
					color[k] = ambient[k] + diffuse[k];
					if (color[k] > 255) { color[k] = 255; }
					if (color[k] < 0) { color[k] = 0; }
				}
				for (int k = 0; k < 3; k++) {
					image(i, j, k) = static_cast<unsigned char>(color[k]);
				}
			}
			curr_point = curr_point - sideways;
		}
		row_start = row_start - up;
	}
	image.normalize(0, 255);
	image.display("Hohol");

}
