#include "Matrix.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	mat::Mat4 mat4(true);
	std::cout << mat4.translate(mat::Vec3(1, 3, 2)).rotateDeg(60, mat::Vec3(1, 2, 3));
	mat::Vec3 vec3 = mat::Vec3(1, 3, 2);
	mat::Vec3 vec = mat::Vec3(mat::Vec3(1, 2, 3).normalize());
	std::cout << vec;
	return 0;
}
