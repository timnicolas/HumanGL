#include "Quaternion.hpp"

#include <cmath>

using namespace mat;

Quaternion::Quaternion(const Vec3 &v, float degrees) :
vec(Vec3()) {
	float rad = degrees / 360 * (float)M_PI * 2;
	vec = Vec3(v * sin(rad/2));
	w = std::cos(rad/2);
}
Quaternion::Quaternion() : Quaternion(Vec3(1, 0, 0), 0) {}

const Quaternion Quaternion::inverted() const {
	Quaternion ret;
	ret.w = w;
	ret.vec = Vec3(vec * -1);
	return ret;
}

const Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion r;

	r.w = w * q.w - vec.dot(q.vec);
	r.vec = Vec3(vec * q.w + q.vec * w + vec.cross(q.vec));

	return r;
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
	toAxisAngle(n, a);
	float at = a * t;
	return Quaternion(n, at);
}

/*
do a smooth rotation btw 2 points by varying step from 0 to 1
*/
const Quaternion Quaternion::slerp(const Quaternion &to, float step) const
{
	const Quaternion &src = *this;

	return ((to * src.inverted()) ^ step) * src;
}

void Quaternion::toAxisAngle(Vec3 &vecAxis, float &flAngle) const
{
	// Convert the quaternion back into axis/angle
	if (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z < 0.0001f)
		vecAxis = Vec3(1, 0, 0);
	else
		vecAxis = Vec3(vec.normalize());

	flAngle = std::acos(w) * 2;
	flAngle *= 360 / ((float)M_PI * 2);
}

namespace mat {
	std::ostream &operator<<(std::ostream &out, const Quaternion &q) {
		out << q.w << " + " << q.vec.x << "i + " << q.vec.y << "j + " << q.vec.z << "k";
		return out;
	}
}