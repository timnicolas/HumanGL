#include "Matrix.hpp"
#include <cmath>
#include <stdio.h>

using namespace mat;

/*
--------------------------------------------------------------------------------
Vec2
*/
Vec2::Vec2() : Vec(2) {}
Vec2::Vec2(const Vec2 &vec) : Vec(vec.getSize(), vec.getData()) {}
Vec2::Vec2(const BaseMat &mat) : Vec(2, mat.getData()) {}
Vec2::Vec2(std::vector<float> data) : Vec(2, data) {}
Vec2::Vec2(float _x, float _y) : Vec(2, std::vector<float>{_x, _y}) {}

namespace mat {
	Vec2 operator*(const Vec2 &v, const float other) { return Vec2(BaseMat(v) * other); }
	Vec2 operator+(const Vec2 &v, const float other) { return Vec2(BaseMat(v) + other); }
	Vec2 operator+(const Vec2 &v, const BaseMat other) { return Vec2(BaseMat(v) + other); }
	Vec2 operator-(const Vec2 &v, const float other) { return Vec2(BaseMat(v) - other); }
	Vec2 operator-(const Vec2 &v, const BaseMat other) { return Vec2(BaseMat(v) - other); }
}

Vec2::~Vec2() {}

/*
--------------------------------------------------------------------------------
Vec3
*/
Vec3::Vec3() : Vec(3) {}
Vec3::Vec3(const Vec3 &vec) : Vec(vec.getSize(), vec.getData()) {}
Vec3::Vec3(const Vec4 &vec4) : Vec(3, std::vector<float>{vec4.x, vec4.y, vec4.z}) {}
Vec3::Vec3(const BaseMat &mat) : Vec(3, mat.getData()) {}
Vec3::Vec3(std::vector<float> data) : Vec(3, data) {}
Vec3::Vec3(float _x, float _y, float _z) : Vec(3, std::vector<float>{_x, _y, _z}) {}

Vec3 Vec3::cross(const Vec3 &v) const
{
	Vec3 c;

	c.x = y * v.z - z * v.y;
	c.y = z * v.x - x * v.z;
	c.z = x * v.y - y * v.x;

	return c;
}
float Vec3::dot(const Vec3 &v) const
{
	float res = 0;
	for (int i=0; i < getSize(); i++) {
		res += get(i) * v.get(i);
	}
	return res;
}

namespace mat {
	Vec3 operator*(const Vec3 &v, const float other) { return Vec3(BaseMat(v) * other); }
	Vec3 operator+(const Vec3 &v, const float other) { return Vec3(BaseMat(v) + other); }
	Vec3 operator+(const Vec3 &v, const BaseMat other) { return Vec3(BaseMat(v) + other); }
	Vec3 operator-(const Vec3 &v, const float other) { return Vec3(BaseMat(v) - other); }
	Vec3 operator-(const Vec3 &v, const BaseMat other) { return Vec3(BaseMat(v) - other); }
}

Vec3::~Vec3() {}

/*
--------------------------------------------------------------------------------
Vec4
*/
Vec4::Vec4() : Vec(4, std::vector<float>{0, 0, 0, 1}) {}
Vec4::Vec4(const Vec4 &vec) : Vec(vec.getSize(), vec.getData()) {}
Vec4::Vec4(const Vec3 &vec3) : Vec(4, std::vector<float>{vec3.x, vec3.y, vec3.z, 1}) {}
Vec4::Vec4(const BaseMat &mat) : Vec(4, mat.getData()) {}
Vec4::Vec4(std::vector<float> data) : Vec(4, data) {}
Vec4::Vec4(float _x, float _y, float _z, float _w) : Vec(4, std::vector<float>{_x, _y, _z, _w}) {}

namespace mat {
	Vec4 operator*(const Vec4 &v, const float other) { return Vec4(BaseMat(v) * other); }
	Vec4 operator+(const Vec4 &v, const float other) { return Vec4(BaseMat(v) + other); }
	Vec4 operator+(const Vec4 &v, const BaseMat other) { return Vec4(BaseMat(v) + other); }
	Vec4 operator-(const Vec4 &v, const float other) { return Vec4(BaseMat(v) - other); }
	Vec4 operator-(const Vec4 &v, const BaseMat other) { return Vec4(BaseMat(v) - other); }
}

Vec4::~Vec4() {}

/*
--------------------------------------------------------------------------------
Mat2
*/
Mat2::Mat2(bool identity) : SquareMat(2, identity) {}
Mat2::Mat2(SquareMat mat) : SquareMat(mat.getSize(), mat.getData()) {}
Mat2::Mat2(std::vector<float> data) : SquareMat(2, data) {}

namespace mat {
	Mat2 operator*(Mat2 m, const float other) { return Mat2(BaseMat(m) * other); }
	Mat2 operator*(Mat2 m, const BaseMat other) { return Mat2(BaseMat(m) * other); }
	Mat2 operator+(Mat2 m, const float other) { return Mat2(BaseMat(m) + other); }
	Mat2 operator+(Mat2 m, const BaseMat other) { return Mat2(BaseMat(m) + other); }
	Mat2 operator-(Mat2 m, const float other) { return Mat2(BaseMat(m) - other); }
	Mat2 operator-(Mat2 m, const BaseMat other) { return Mat2(BaseMat(m) - other); }
}

Mat2::~Mat2() {}

/*
--------------------------------------------------------------------------------
Mat3
*/
Mat3::Mat3(bool identity) : SquareMat(3, identity) {}
Mat3::Mat3(SquareMat mat) : SquareMat(mat.getSize(), mat.getData()) {}
Mat3::Mat3(std::vector<float> data) : SquareMat(3, data) {}

namespace mat {
	Mat3 operator*(Mat3 m, const float other) { return Mat3(BaseMat(m) * other); }
	Mat3 operator*(Mat3 m, const BaseMat other) { return Mat3(BaseMat(m) * other); }
	Mat3 operator+(Mat3 m, const float other) { return Mat3(BaseMat(m) + other); }
	Mat3 operator+(Mat3 m, const BaseMat other) { return Mat3(BaseMat(m) + other); }
	Mat3 operator-(Mat3 m, const float other) { return Mat3(BaseMat(m) - other); }
	Mat3 operator-(Mat3 m, const BaseMat other) { return Mat3(BaseMat(m) - other); }
}

Mat3::~Mat3() {}

/*
--------------------------------------------------------------------------------
Mat4
*/
Mat4::Mat4(bool identity) : SquareMat(4, identity) {}
Mat4::Mat4(SquareMat mat) : SquareMat(mat.getSize(), mat.getData()) {}
Mat4::Mat4(std::vector<float> data) : SquareMat(4, data) {}

Mat4 Mat4::scale(float valX, float valY, float valZ) {
	Mat4 res = *this;
	res.get(0, 0) *= valX;
	res.get(1, 1) *= valY;
	res.get(2, 2) *= valZ;
	return res;
}
Mat4 Mat4::scale(float val) {
	return scale(val, val, val);
}
Mat4 Mat4::scale(Vec3 val) {
	return scale(val.x, val.y, val.z);
}

Mat4 Mat4::translate(float valX, float valY, float valZ) {
	Mat4 res = *this;
	res.get(0, 3) += valX;
	res.get(1, 3) += valY;
	res.get(2, 3) += valZ;
	return res;
}
Mat4 Mat4::translate(Vec3 val) {
	return translate(val.x, val.y, val.z);
}
Mat4 Mat4::rotateRad(float radians, float axX, float axY, float axZ) {
	Vec3 vec = Vec3(Vec3(axX, axY, axZ).normalize());
	axX = vec.x;
	axY = vec.y;
	axZ = vec.z;
	Mat4 res = Mat4();
	float cosA = std::cos(radians);
	float sinA = std::sin(radians);
	res.get(0, 0) = cosA + std::pow(axX, 2) * (1 - cosA);
	res.get(0, 1) = axX * axY * (1 - cosA) - axZ * sinA;
	res.get(0, 2) = axX * axZ * (1 - cosA) + axY * sinA;
	res.get(1, 0) = axY * axX * (1 - cosA) + axZ * sinA;
	res.get(1, 1) = cosA + std::pow(axY, 2) * (1 - cosA);
	res.get(1, 2) = axY * axZ * (1 - cosA) - axX * sinA;
	res.get(2, 0) = axZ * axX * (1 - cosA) - axY * sinA;
	res.get(2, 1) = axZ * axY * (1 - cosA) + axX * sinA;
	res.get(2, 2) = cosA + std::pow(axZ, 2) * (1 - cosA);
	res = *this * res;
	return res;
}
Mat4 Mat4::rotateRad(float radians, Vec3 axis) {
	return rotateRad(radians, axis.x, axis.y, axis.z);
}
Mat4 Mat4::rotateDeg(float degrees, float axX, float axY, float axZ) {
	return rotateRad(degrees * (M_PI / 180), axX, axY, axZ);
}
Mat4 Mat4::rotateDeg(float degrees, Vec3 axis) {
	return rotateDeg(degrees, axis.x, axis.y, axis.z);
}

Mat4 Mat4::lookAt(const Vec3 &src, const Vec3 &dst) {
	Mat4 res = Mat4();
	Vec3 tmpUp = Vec3(0, 1, 0);
	Vec3 fwd = normalize(dst - src);
	Vec3 side = normalize(cross(fwd, tmpUp));
	Vec3 up = normalize(cross(side, fwd));
	res.get(0, 0) = side.x;
	res.get(0, 1) = side.y;
	res.get(0, 2) = side.z;
	res.get(1, 0) = up.x;
	res.get(1, 1) = up.y;
	res.get(1, 2) = up.z;
	res.get(2, 0) = -fwd.x;
	res.get(2, 1) = -fwd.y;
	res.get(2, 2) = -fwd.z;

	res.get(0, 3) = -dot(side, src);
	res.get(1, 3) = -dot(up, src);
	res.get(2, 3) = dot(fwd, src);
	return res;
}
Mat4 Mat4::perspective(float fov_y, float aspect, float z_near, float z_far) {
	Mat4 res = *this;

	if (aspect == 0) {
		std::cout << "perspective aspect can't be set to 0.0" << std::endl;
		return Mat4();
	}
	if (z_near >= z_far) {
		std::cout << "perspective near is bigger than far value" << std::endl;
		return Mat4();
	}
	float tanHalfFov = std::tan(fov_y / 2);
	res.get(0, 0) = 1 / (aspect * tanHalfFov);
	res.get(1, 1) = 1 / (tanHalfFov);
	res.get(2, 2) = -(z_far + z_near) / (z_far - z_near);
	res.get(2, 3) = -(2 * z_far * z_near) / (z_far - z_near);
	res.get(3, 2) = -1;
	return res;
}

namespace mat {
	Mat4 operator*(Mat4 m, const float other) { return Mat4(BaseMat(m) * other); }
	Mat4 operator*(Mat4 m, const BaseMat other) { return Mat4(BaseMat(m) * other); }
	Mat4 operator+(Mat4 m, const float other) { return Mat4(BaseMat(m) + other); }
	Mat4 operator+(Mat4 m, const BaseMat other) { return Mat4(BaseMat(m) + other); }
	Mat4 operator-(Mat4 m, const float other) { return Mat4(BaseMat(m) - other); }
	Mat4 operator-(Mat4 m, const BaseMat other) { return Mat4(BaseMat(m) - other); }
}

Mat4::~Mat4() {}

/*
--------------------------------------------------------------------------------
Vec
*/
Vec::Vec(int size) :
BaseMat(size, 1),
x(get(0)),
y(get((getSize() >= 2) ? 1 : 0)),
z(get((getSize() >= 3) ? 2 : 0)),
w(get((getSize() >= 4) ? 3 : 0)),
r(get(0)),
g(get((getSize() >= 2) ? 1 : 0)),
b(get((getSize() >= 3) ? 2 : 0)) {
}
Vec::Vec(BaseMat mat) : Vec(mat.getLns(), mat.getData()) {}
Vec::Vec(int size, std::vector<float> data) :
BaseMat(size, 1, data),
x(get(0)),
y(get((getSize() >= 2) ? 1 : 0)),
z(get((getSize() >= 3) ? 2 : 0)),
w(get((getSize() >= 4) ? 3 : 0)),
r(get(0)),
g(get((getSize() >= 2) ? 1 : 0)),
b(get((getSize() >= 3) ? 2 : 0)) {
}

int Vec::getSize() const { return getLns(); }
const float &Vec::get(int x) const { return (*_data)[x]; }
float &Vec::get(int x) { return (*_data)[x]; }
float &Vec::operator[](const int idx) { return get(idx); }
const float &Vec::operator[](const int idx) const { return get(idx); }

Vec &Vec::operator=(const Vec &other) {
	if(&other == this)
		return *this;
	this->setLns(other.getLns());
	this->setCols(other.getCols());
	this->getData() = other.getData();
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	return *this;
}

Vec Vec::normalize() const {
	Vec norm = Vec(getSize(), getData());
	float len = 0;
	for (int i=0; i < getSize(); i++) {
		len += get(i) * get(i);
	}
	if (len > 0) {
		len = std::sqrt(len);
		for (int i=0; i < getSize(); i++) {
			norm.get(i) /= len;
		}
	}
	return norm;
}

float Vec::dot(const Vec &v) const
{
	if (getSize() != v.getSize()) {
		throw std::invalid_argument("wrong vector size");
	}
	float res = 0;
	for (int i=0; i < getSize(); i++) {
		res += get(i) * v.get(i);
	}
	return res;
}

namespace mat {
	Vec operator*(const Vec &v, const float other) { return Vec(BaseMat(v) * other); }
	Vec operator+(const Vec &v, const float other) { return Vec(BaseMat(v) + other); }
	Vec operator+(const Vec &v, const BaseMat other) { return Vec(BaseMat(v) + other); }
	Vec operator-(const Vec &v, const float other) { return Vec(BaseMat(v) - other); }
	Vec operator-(const Vec &v, const BaseMat other) { return Vec(BaseMat(v) - other); }
}

Vec::~Vec() {}

/*
--------------------------------------------------------------------------------
SquareMat
*/
SquareMat::SquareMat(int size, bool identity) : BaseMat(size) {
	if (!identity) {
		for (int i=0; i < getSize(); i++) {
			get(i, i) = 0;
		}
	}
}
SquareMat::SquareMat(BaseMat mat) : BaseMat(mat.getLns(), mat.getCols(), mat.getData()) {}
SquareMat::SquareMat(int size, std::vector<float> data) : BaseMat(size, size, data) {}
int SquareMat::getSize() const { return getLns(); }

namespace mat {
	SquareMat operator*(SquareMat m, const float other) { return SquareMat(BaseMat(m) * other); }
	SquareMat operator*(SquareMat m, const BaseMat other) { return SquareMat(BaseMat(m) * other); }
	SquareMat operator+(SquareMat m, const float other) { return SquareMat(BaseMat(m) + other); }
	SquareMat operator+(SquareMat m, const BaseMat other) { return SquareMat(BaseMat(m) + other); }
	SquareMat operator-(SquareMat m, const float other) { return SquareMat(BaseMat(m) - other); }
	SquareMat operator-(SquareMat m, const BaseMat other) { return SquareMat(BaseMat(m) - other); }
}

SquareMat::~SquareMat() {}

/*
--------------------------------------------------------------------------------
BaseMat
*/
BaseMat::BaseMat(int lns, int cols, std::vector<float> data) :
_lns(lns),
_cols(cols),
_data(new std::vector<float>()) {
	getData() = data;
}
BaseMat::BaseMat(int lns, int cols) :
_lns(lns),
_cols(cols),
_data(new std::vector<float>()) {
	for (int i = 0; i < getCols(); i++) {
		for (int j = 0; j < getLns(); j++) {
			getData().push_back(0);
		}
	}
}
BaseMat::BaseMat(int size) :
_lns(size),
_cols(size),
_data(new std::vector<float>()) {
	for (int i = 0; i < getCols(); i++) {
		for (int j = 0; j < getLns(); j++) {
			getData().push_back(((i == j) ? 1 : 0));
		}
	}
}
BaseMat::BaseMat(const BaseMat &m) :
_lns(m.getLns()),
_cols(m.getCols()),
_data(new std::vector<float>()) {
	*this = m;
}

void BaseMat::setLns(int lns) { _lns = lns; }
void BaseMat::setCols(int cols) { _cols = cols; }
int BaseMat::getCols() const { return _cols; }
int BaseMat::getLns() const { return _lns; }
const std::vector<float> &BaseMat::getData() const { return *_data; }
std::vector<float> &BaseMat::getData() { return *_data; }
const float &BaseMat::get(int ln, int col) const { return (*_data)[ln * _cols + col]; }
float &BaseMat::get(int ln, int col) { return (*_data)[ln * _cols + col]; }

std::string BaseMat::getPrintableNb(float nb) const {
	char *str;
	if (nb < 100000 && nb > -10000) {
		asprintf(&str, "%8.2f", nb);
	}
	else if (nb < 1000000 && nb > -100000) {
		asprintf(&str, "%8.1f", nb);
	}
	else if (nb < 100000000 && nb > -10000000) {
		asprintf(&str, "%8.0f", nb);
	}
	else {
		asprintf(&str, "%8.0g", nb);
	}
	return str;
}

/*
operators
*/
namespace mat {
	std::ostream &operator<<(std::ostream &out, const BaseMat &m) {
		for (int i=0; i < m.getLns(); i++) {
			out << "| ";
			for (int j=0; j < m.getCols(); j++) {
				out << m.getPrintableNb(m.get(i, j)) << " ";
			}
			out << "|\n";
		}
		return out;
	}
	BaseMat operator*(BaseMat m, const float other) {
		BaseMat res = m;
		for (int i=0; i < m.getLns() * m.getCols(); i++) {
			res.getData()[i] = res.getData()[i] * other;
		}
		return res;
	}
	BaseMat operator*(BaseMat m, const BaseMat other) {
		if (m.getCols() != other.getLns()) {
			throw std::invalid_argument("wrong matrix size");
		}
		BaseMat res = BaseMat(m.getLns(), other.getCols());
		for (int ln=0; ln < res.getLns(); ln++) {
			for (int col=0; col < res.getCols(); col++) {
				float r = 0;
				for (int i=0; i < m.getCols(); i++) {
					r += m.get(ln, i) * other.get(i, col);
				}
				res.get(ln, col) = r;
			}
		}
		return res;
	}
	BaseMat operator+(BaseMat m, const float other) {
		BaseMat res = m;
		for (int i=0; i < m.getLns() * m.getCols(); i++) {
			res.getData()[i] = res.getData()[i] + other;
		}
		return res;
	}
	BaseMat operator+(BaseMat m, const BaseMat other) {
		if (m.getLns() != other.getLns() || m.getCols() != other.getCols()) {
			throw std::invalid_argument("wrong matrix size");
		}
		BaseMat res = m;
		for (int ln=0; ln < res.getLns(); ln++) {
			for (int col=0; col < res.getCols(); col++) {
				res.get(ln, col) += other.get(ln, col);
			}
		}
		return res;
	}
	BaseMat operator-(BaseMat m, const float other) {
		BaseMat res = m;
		for (int i=0; i < m.getLns() * m.getCols(); i++) {
			res.getData()[i] = res.getData()[i] - other;
		}
		return res;
	}
	BaseMat operator-(BaseMat m, const BaseMat other) {
		if (m.getLns() != other.getLns() || m.getCols() != other.getCols()) {
			throw std::invalid_argument("wrong matrix size");
		}
		BaseMat res = m;
		for (int ln=0; ln < res.getLns(); ln++) {
			for (int col=0; col < res.getCols(); col++) {
				res.get(ln, col) -= other.get(ln, col);
			}
		}
		return res;
	}
	bool operator==(BaseMat m, const BaseMat other) {
		if (m.getLns() != other.getLns() || m.getCols() != other.getCols()) {
			return false;
		}
		for (int i=0; i < m.getLns(); i++) {
			for (int j=0; j < m.getCols(); j++) {
				if (m[i][j] != other[i][j])
					return false;
			}
		}
		return true;
	}
	BaseMat &BaseMat::operator=(const BaseMat &other) {
        if(&other == this)
            return *this;
		this->setLns(other.getLns());
		this->setCols(other.getCols());
		this->getData() = other.getData();
        return *this;
	}
}

BaseMat::~BaseMat() {
	delete _data;
}

/*
--------------------------------------------------------------------------------
utils
*/
namespace mat {
	float radians(float deg) { return deg / (180 / M_PI); }
	float degrees(float rad) { return rad * (180 / M_PI); }

	Vec3 normalize(const Vec3 &vec) { return vec.normalize(); }
	Mat4 lookAt(const Vec3 &src, const Vec3 &dst) { return Mat4().lookAt(src, dst); }
	Vec3 cross(const Vec3 &vec1, const Vec3 &vec2) { return vec1.cross(vec2); }
	float dot(const Vec3 &vec1, const Vec3 &vec2) { return vec1.dot(vec2); }
	Mat4 perspective(float fov_y, float aspect, float z_near, float z_far) {
		return Mat4(false).perspective(fov_y, aspect, z_near, z_far);
	}
}