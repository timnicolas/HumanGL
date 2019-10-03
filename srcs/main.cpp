#include "Matrix.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	mat::Mat4 mat4(true);
	std::cout << mat4.rotateDeg(90, 1, 0, 0);
	mat::Vec4 vec = mat::Vec4();
	vec.x = 300000000;
	vec.y = 30000000;
	vec.z = 50000.25;
	std::cout << vec;
	mat::Vec3 color = mat::Vec3();
	color.g = 5.2;
	color.b = 500.25;
	std::cout << "color:\n" << color;
	return 0;
}
