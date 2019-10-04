#include "Matrix.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	mat::Mat4 mat4(true);
	std::cout << mat4.translate(mat::Vec3(1, 3, 2)).rotateDeg(60, mat::Vec3(1, 2, 3));
	mat::Vec3 vec3 = mat::Vec3(1, 3, 2);
	mat::Vec3 vec = mat::Vec3(mat::Vec3(1, 2, 3).normalize());
	std::cout << vec;
	std::vector<float> raw1 = static_cast<std::vector<float>>(mat4);
	float *raw2 = static_cast<float*>(mat4);
	std::cout << raw1[14] << raw1[15] << "\n";
	std::cout << raw2[14] << raw2[15] << "\n";
	return 0;
}
