#include "Matrix.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	mat::Mat4 mat4(true);
	std::cout << mat4.scale(2).rotateDeg(90, 1, 0, 0).translate(12, 3, -5);
	return 0;
}
