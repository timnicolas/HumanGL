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

	/*
	return (q * p * q.inverted()).vec;
	*/

	Vec3 vcV = vec;
	return Vec3(other + vcV * (2 * w) + vec.cross(vcV) * 2);
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

const Quaternion Quaternion::slerp(const Quaternion &other, float t) const
{
	const Quaternion &q = *this;
	Quaternion r = other;

	// return ((r * q.Inverted()) ^ t) * q;

	float flCosOmega = w * r.w + r.vec.dot(vec);
	if (flCosOmega < 0)
	{
		// Avoid going the long way around.
		r.w = -r.w;
		r.vec = Vec3(r.vec * -1);
		flCosOmega = -flCosOmega;
	}

	float k0, k1;
	if (flCosOmega > 0.9999f)
	{
		// Very close, use a linear interpolation.
		k0 = 1 - t;
		k1 = t;
	}
	else
	{
		// Trig identity, sin^2 + cos^2 = 1
		float flSinOmega = std::sqrt(1 - flCosOmega * flCosOmega);

		// Compute the angle omega
		float flOmega = std::atan2(flSinOmega, flCosOmega);
		float flOneOverSinOmega = 1 / flSinOmega;

		k0 = std::sin((1 - t) * flOmega) * flOneOverSinOmega;
		k1 = std::sin(t * flOmega) * flOneOverSinOmega;
	}

	// Interpolate
	Quaternion result;
	result.w = q.w * k0 + r.w * k1;
	result.vec = Vec3(q.vec * k0 + r.vec * k1);

	return result;
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