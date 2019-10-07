#include "Matrix.hpp"
#include "Quaternion.hpp"

int main(int ac, char **av) {
	(void)ac;
	(void)av;
	mat::Vec3 lookat = mat::Vec3(mat::Vec3(1, 2, 0).normalize());
	float rotateDeg = 90;
	std::cout << lookat;

	mat::Mat4 rotateMat = mat::Mat4();  // identity
	rotateMat = rotateMat.rotateDeg(rotateDeg, lookat);
	std::cout << "rotation matrix:\n" << rotateMat;

	mat::Quaternion rotateQuat = mat::Quaternion(lookat, rotateDeg);
	std::cout << "quaterion: " << rotateQuat << "\n";

	mat::Vec3 axisAngle;
	float angle;
	rotateQuat.toAxisAngle(axisAngle, angle);
	std::cout << angle << "\n" << axisAngle;

	mat::Vec4 basePoint = mat::Vec4(4, 1, 8);
	std::cout << "rotate with matrix:\n" << rotateMat * basePoint;
	std::cout << "rotate with Quaternion:\n" << rotateQuat * basePoint;

	float rotateDegTo = 180;
	mat::Quaternion to = mat::Quaternion(lookat, rotateDegTo);
	std::cout << "\nbase point:\n" << basePoint << "\n";
	std::cout << "to point:\n" << to * basePoint << "\n";
	for (float i=0; i <= 1; i+= 0.2) {
		std::cout << "rotate of " << i << ":\n" << rotateQuat.slerp(to, i) * basePoint << "\n";
	}
	return 0;
}
