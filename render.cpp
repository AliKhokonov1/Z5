#include"VecPoint.h"
#include"Shape.h"
#include<vector>
#include"CImg.h"
#include <chrono>
void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*>& objects) {
	VecPoint sideways, start;
	double pixel_size;
	double screen_height = 2*(screen * tan(alpha/2));
	double screen_width = screen_height * width / height;
	pixel_size = screen_height / height;
	screen_width = static_cast<double>(width) * pixel_size;
	normal = normal * (1 / normal.lenght());
	up = up * (1 / up.lenght());
	sideways.x = up.y * normal.z - up.z * normal.y;
	sideways.y = up.z * normal.x - up.x * normal.z;
	sideways.z = up.x * normal.y - up.y * normal.x;

	start = normal * screen + sideways * ((screen_width - pixel_size) / 2.0) + up * ((screen_height - pixel_size) / 2.0);

	using namespace cimg_library;

	CImg<unsigned char> image(width, height, 1, 3, 0);
	VecPoint Ntmp, N, L;
	VecPoint ray_begin = cam;
	VecPoint ray_direction;
	Shape* obj=nullptr;
	double t, tmin = std::numeric_limits<double>::max();
	double ambient[3];
	double diffuse[3];
	double color[3];
	double NL;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			ray_direction = start - sideways * (pixel_size * i) - up * (pixel_size * j);
			ray_direction = ray_direction * (1 / screen);
			tmin = std::numeric_limits<double>::max();
			for (int k = 0; k < objects.size(); k++) {
				if (objects[k]->intersect(ray_begin, ray_direction,t,Ntmp,screen,limit)) {//Надо еще лимит в интерсект добавить 
					if (t < tmin && t > screen) {
						N = Ntmp;
						tmin = t;
						obj = objects[k];
					}
				}
			}
			if (tmin > limit) {
				image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
			}
			else {
				N = N * (1 / (1 / N.lenght()));
				L = (light - (ray_direction * tmin + ray_begin));
				L = L * (1 / (1 / L.lenght()));
				NL = N*L;
				if (NL < 0) {
					NL = 0.0;
				}
				for (int k = 0; k < 3; k++) {
					ambient[k] = (0.2 * (obj->color[k]));
				}
				for (int k = 0; k < 3; k++) {
					diffuse[k] = (0.7 * NL * (obj->color[k]));
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
		}
	}

	image.normalize(0, 255);
	image.display("Hohol");

}
						

