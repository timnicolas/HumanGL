#pragma once

#include "Matrix.hpp"

namespace mat {
	class Quaternion {
		public:
			Quaternion();
			Quaternion(float degrees, const Vec3 &v);

			const Quaternion inverted() const;
			const Quaternion operator*(const Quaternion &other) const;  // multiplication btw 2 rotations
			const Vec3 operator*(const Vec3 &other) const;  // apply rotation to the vector
			const Vec4 operator*(const Vec4 &other) const;  // apply rotation to the vector
			const Quaternion operator^(float t) const;
			const Quaternion slerp(const Quaternion &to, float step) const;  // get a point btw this and to (with t btw 0 & 1)
			const Quaternion normalize() const;

			void toAxisAngle(float &flAngle, Vec3 &vecAxis) const;  // get axis and angle from quaterion
			Mat4 toMatrix() const;

			/* operators */
			friend std::ostream &operator<<(std::ostream &out, const Quaternion &q);

			Vec3 vec;  // x, y, z
			float w;
		protected:
		private:
	};
	const Quaternion slerp(const Quaternion &from, const Quaternion &to, float step);
}

/*
// example -> creating quaternion
mat::Vec3 lookat = mat::Vec3(1, 2, 0).normalize();
float rotateDeg = 25;

std::cout << "rotation of " << rotateDeg << "deg on vector:\n" << lookat;

mat::Quaternion rotateQuat = mat::Quaternion(rotateDeg, lookat);
std::cout << "quaterion: " << rotateQuat << "\n";
std::cout << "quaterion matrix: \n" << rotateQuat.toMatrix() << "\n";
*/

/*
// example -> smooth rotation
// apply a smooth rotation on an object using slerp (step from 0 to 1)

// define src axis and angle
mat::Vec3 baseAxis = mat::Vec3(mat::Vec3(1, 2, 0).normalize());
float baseAngle = 90;
// define dest axis and angle
mat::Vec3 toAxis = mat::Vec3(mat::Vec3(-4, 5, 1).normalize());
float toAngle = 100;
// define the point to move
mat::Vec4 basePoint = mat::Vec4(4, 1, 8);

mat::Quaternion baseQuat = mat::Quaternion(baseAngle, baseAxis);
mat::Quaternion toQuat = mat::Quaternion(toAngle, toAxis);

std::cout << "base point:\n" << baseQuat * basePoint << "\n";
std::cout << "to point:\n" << toQuat * basePoint << "\n";
for (float i=0; i <= 1; i+= 0.2) {
	std::cout << "rotate of " << i << ":\n" << baseQuat.slerp(toQuat, i) * basePoint;
}
// then process with final rotation
std::cout << "final position:\n" << toQuat * basePoint << "\n";
*/