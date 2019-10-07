#include "Matrix.hpp"
#include "Quaternion.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	// example -> creating quaternion
	mat::Vec3 lookat = mat::Vec3(1, 2, 0).normalize();
	float rotateDeg = 25;

	std::cout << "rotation of " << rotateDeg << "deg on vector:\n" << lookat;

	mat::Quaternion rotateQuat = mat::Quaternion(rotateDeg, lookat);
	std::cout << "quaterion: " << rotateQuat << "\n";
	std::cout << "quaterion matrix: \n" << rotateQuat.toMatrix() << "\n";

	mat::BaseMat mat = mat::BaseMat(3, 1, std::vector<float>{1, 2, 3});
	mat::Vec3 vec = mat::Vec3(mat);
	return 0;
}
