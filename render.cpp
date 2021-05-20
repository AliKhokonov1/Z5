#include"VecPoint.h"
#include"Shape.h"
#include<vector>
#include"CImg.h"
void render(VecPoint cam, VecPoint normal, VecPoint up, double screen, double limit, double alpha, int width, int height, VecPoint light, std::vector<Shape*> &objects){
	
	VecPoint N;//������� � �����������
	double t;
	VecPoint L;//����������� �� ����� ����������� �� ��������� �����
	double NL;//��������� ������������ �, L

	VecPoint ray_begin = cam;
	VecPoint ray_direction;

	VecPoint sideway;
	sideway.x = up.y * normal.z - up.z * normal.y;
	sideway.y = up.z * normal.x - up.x * normal.z;
	sideway.z = up.x * normal.y - up.y * normal.x;

	double screen_height = screen * sin(alpha);
	double screen_width = screen_height * width/height;
	double pixel_size = screen_height / height;

	double color[3];//���� ������� = AMBIENT + DIFFUSE
	double ambient[3];//������� ������������ ���������
	double diffuse[3];//������������ ������������ ���������

	VecPoint start;
	start = normal * screen + sideway * ((screen_width - pixel_size)/2)+up*((screen_height-pixel_size)/2);//������ ������ �������� ����

	Shape* obj = nullptr;

	double tmin = DBL_MAX;

	using namespace cimg_library;
	CImg<unsigned char> image(width, height, 1, 3, 0);
	bool intersect = false;
	for (int i = 0;i < width;i++) {
		for (int j = 0;j < height;j++) {
			ray_direction = start - sideway * pixel_size * (i)-up * pixel_size * (j);//������ ����
			intersect = false;
			for (int k = 0; k < objects.size(); k++) {
				if (objects[k]->intersect(ray_begin, ray_direction, N, t)) {
					intersect = true;
					if (t < tmin) {
						tmin = t;
						obj = objects[k];
					}
				}
			}
			if (!intersect) {
				//��� �� �������� �� � ���
				//����������� ������ ������
				for (int k = 0; k < 3; k++) {
					image(i, j, k) = 0;
				}
			}
			else {
				//��� ��������
				//����� ����
				N = N * (1 / sqrt(N.x * N.x + N.y * N.y + N.z * N.z));
				L = (light - (ray_direction*tmin + ray_begin));
				L = L * (1 / sqrt(L.x*L.x+L.y*L.y+L.z*L.z));
				NL = N.x * L.x + N.y * L.y + N.z * L.z;
				if (NL < 0) {
					NL = 0.0;
				}
				for (int k = 0; k < 3; k++) {
					ambient[k] = (0.3 * (obj->color[k]));
				}
				for (int k = 0; k < 3; k++) {
					diffuse[k] = (NL*(obj->color[k]));//����� ��� �� ��������� ��������� ������ 1 �� ������ 0
				}
				for (int k = 0; k < 3; k++) {
					color[k] = ambient[k]+diffuse[k];
					if (color[k] > 255) { color[k] = 255; }
				}
				for (int k = 0; k < 3; k++) {
					image(i, j, k) = static_cast<unsigned char>(color[k] > 255 ? 255 : color[k] < 0 ? 0 : color[k]);
				}
			}
		}
	}

	image.normalize(0, 255);
	image.display("Hohol");

}