#include "Matrix.hpp"
#include <cmath>
#include <stdio.h>

using namespace mat;

/*
--------------------------------------------------------------------------------
Vec2
*/
Vec2::Vec2() : Vec(2) {}
Vec2::Vec2(std::vector<float> data) : Vec(2, data) {}
Vec2::~Vec2() {}

/*
--------------------------------------------------------------------------------
Vec3
*/
Vec3::Vec3() : Vec(3) {}
Vec3::Vec3(std::vector<float> data) : Vec(3, data) {}
Vec3::~Vec3() {}

/*
--------------------------------------------------------------------------------
Vec4
*/
Vec4::Vec4() : Vec(4, std::vector<float>{0, 0, 0, 1}) {}
Vec4::Vec4(std::vector<float> data) : Vec(4, data) {}
Vec4::~Vec4() {}

/*
--------------------------------------------------------------------------------
Mat2
*/
Mat2::Mat2(bool identity) : SquareMat(2, identity) {}
Mat2::Mat2(std::vector<float> data) : SquareMat(2, data) {}
Mat2::~Mat2() {}

/*
--------------------------------------------------------------------------------
Mat3
*/
Mat3::Mat3(bool identity) : SquareMat(3, identity) {}
Mat3::Mat3(std::vector<float> data) : SquareMat(3, data) {}
Mat3::~Mat3() {}

/*
--------------------------------------------------------------------------------
Mat4
*/
Mat4::Mat4(bool identity) : SquareMat(4, identity) {}
Mat4::Mat4(std::vector<float> data) : SquareMat(4, data) {}

Mat4 Mat4::scale(float valX, float valY, float valZ) {
	Mat4 res = *this;
	res.get(0, 0) = valX;
	res.get(1, 1) = valY;
	res.get(2, 2) = valZ;
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
	res.get(0, 3) = valX;
	res.get(1, 3) = valY;
	res.get(2, 3) = valZ;
	return res;
}
Mat4 Mat4::translate(Vec3 val) {
	return translate(val.x, val.y, val.z);
}
Mat4 Mat4::rotateRad(float radians, float axX, float axY, float axZ) {
	Mat4 res = *this;
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
SquareMat::SquareMat(int size, std::vector<float> data) : BaseMat(size, size, data) {}
int SquareMat::getSize() const { return getLns(); }
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
	for (int i=0; i < getLns() * getCols(); i++) {
		getData().push_back(m.getData()[i]);
	}
}

int BaseMat::getCols() const { return _cols; }
int BaseMat::getLns() const { return _lns; }
const std::vector<float> &BaseMat::getData() const { return *_data; }
std::vector<float> &BaseMat::getData() { return *_data; }
const float &BaseMat::get(int ln, int col) const { return (*_data)[ln * _cols + col]; }
float &BaseMat::get(int ln, int col) { return (*_data)[ln * _cols + col]; }

std::string BaseMat::getPrintableNb(float nb) const {
	char *str;
	if (nb < 100000) {
		if ((int)(nb * 100) / 100 == 0)
			nb = 0;
		asprintf(&str, "%8.2f", nb);
	}
	else if (nb < 1000000) {
		asprintf(&str, "%8.1f", nb);
	}
	else if (nb < 100000000) {
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
}

BaseMat::~BaseMat() {
	delete _data;
}