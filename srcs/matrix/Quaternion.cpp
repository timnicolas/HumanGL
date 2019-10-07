#include "Quaternion.hpp"

#include <cmath>

using namespace mat;

Quaternion::Quaternion(float degrees, const Vec3 &v) :
vec(Vec3()) {
	float rad = degrees / 360 * (float)M_PI * 2;
	vec = Vec3(v * sin(rad/2));
	w = std::cos(rad/2);
}
Quaternion::Quaternion() : Quaternion(0, Vec3(1, 0, 0)) {}

const Quaternion Quaternion::inverted() const {
	Quaternion ret;
	ret.w = w;
	ret.vec = Vec3(vec * -1);
	return ret;
}

const Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion res;

	res.w = w * other.w - vec.dot(other.vec);
	res.vec = Vec3(vec * other.w + other.vec * w + vec.cross(other.vec));

	return res;
}

const Vec3 Quaternion::operator*(const Vec3& other) const
{
	Quaternion p;
	p.w = 0;
	p.vec = other;

	// basic formula = quat * vec * quat.inverted()
	return (*this * p * this->inverted()).vec;
}

const Vec4 Quaternion::operator*(const Vec4& other) const
{
	Quaternion p;
	p.w = 0;
	p.vec = Vec3(other);

	// basic formula = quat * vec * quat.inverted()
	return Vec4((*this * p * this->inverted()).vec);
}

const Quaternion Quaternion::operator^(float t) const
{
	// Convert the quaternion back into axis/angle
	float a;
	Vec3 n;
	toAxisAngle(a, n);
	float at = a * t;
	return Quaternion(at, n);
}

/*
do a smooth rotation btw 2 points by varying step from 0 to 1
*/
const Quaternion Quaternion::slerp(const Quaternion &to, float step) const
{
	const Quaternion &src = *this;

	return ((to * src.inverted()) ^ step) * src;
}

void Quaternion::toAxisAngle(float &flAngle, Vec3 &vecAxis) const
{
	// Convert the quaternion back into axis/angle
	if (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z < 0.0001f)
		vecAxis = Vec3(1, 0, 0);
	else
		vecAxis = Vec3(vec.normalize());

	flAngle = std::acos(w) * 2;
	flAngle *= 360 / ((float)M_PI * 2);
}

Mat4 Quaternion::toMatrix() const {
	Mat4 res = Mat4();  // identity
	float angle;
	Vec3 vec;

	toAxisAngle(angle, vec);
	res = res.rotateDeg(angle, vec);
	return res;
}

namespace mat {
	std::ostream &operator<<(std::ostream &out, const Quaternion &q) {
		out << q.w << " + " << q.vec.x << "i + " << q.vec.y << "j + " << q.vec.z << "k";
		return out;
	}
}