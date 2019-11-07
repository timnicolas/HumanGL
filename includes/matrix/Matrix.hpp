#pragma once

#include <iostream>
#include <vector>
#include <cmath>

namespace mat {
	class Vec;
	class Vec2;
	class Vec3;
	class Vec4;
	class SquareMat;
	class Mat2;
	class Mat3;
	class Mat4;
	class BaseMat {
		public:
			BaseMat(int lns, int cols);  // init with zero matrix
			BaseMat(int size);  // init with identity matrix
			BaseMat(int lns, int cols, std::vector<float> data);  // init with a copy of data
			BaseMat(const BaseMat &m);
			~BaseMat();

			void setLns(int lns);  // set number of lines
			void setCols(int cols);  // set number of columns
			int getLns() const;  // get number of lines
			int getCols() const;  // get number of columns
			const std::vector<float> &getData() const;  // get all data as a vector
			std::vector<float> &getData();
			float &get(int ln, int col);  // get one data (line, column)
			const float &get(int ln, int col) const;
			std::string getPrintableNb(float nb) const;  // get a printable number (for cout)

			/* operators */
			friend std::ostream &operator<<(std::ostream &out, const BaseMat &m);
			friend BaseMat operator*(BaseMat m, const float other);
			friend BaseMat operator*(BaseMat m, const BaseMat other);
			friend BaseMat operator+(BaseMat m, const float other);
			friend BaseMat operator+(BaseMat m, const BaseMat other);
			friend BaseMat operator-(BaseMat m, const float other);
			friend BaseMat operator-(BaseMat m, const BaseMat other);
			friend bool operator==(BaseMat m, const BaseMat other);
			BaseMat &operator=(const BaseMat &other);
			explicit operator std::vector<float>() const { return *_data; };
			explicit operator float*() const { return static_cast<float*>(&(*_data)[0]); };

			// operator [][]
			class Dim2 {
				public:
					Dim2(std::vector<float> *mat, int offset) : _mat(mat), _offset(offset) {}
					float &operator[](int col) { return (*_mat)[_offset + col]; }
					const float &operator[](int col) const { return (*_mat)[_offset + col]; }
				private:
					std::vector<float> *_mat;
					int _offset;
			};
			Dim2 operator[](int line) { return Dim2(_data, line * _cols); }
			const Dim2 operator[](int line) const { return Dim2(_data, line * _cols); }

		protected:
			int _lns;  // number of lines (height)
			int _cols;  // number of columns (width)
			/*
			for the Matrix:
			| 1 2 |
			| 3 4 |
			float *data = {1, 2, 3, 4};
			*/
			std::vector<float> *_data;  // all data
		private:
	};

	class Vec : public BaseMat {
		public:
			Vec(int size);
			Vec(BaseMat mat);
			Vec(int size, std::vector<float> data);
			~Vec();

			int getSize() const;
			const float &get(int x) const;
			float &get(int x);
			const float &operator[](const int idx) const;
			float &operator[](const int idx);
			Vec &operator=(const Vec &other);
			float dot(const Vec &v) const;
			Vec normalize() const;

			/*
			xyzw and rgb are 'shortcut' to acces to the datas
			*/
			float &x;
			float &y;
			float &z;
			float &w;
			float &r;
			float &g;
			float &b;

			friend Vec operator*(const Vec &v, const float other);
			friend Vec operator+(const Vec &m, const float other);
			friend Vec operator+(const Vec &m, const BaseMat other);
			friend Vec operator-(const Vec &m, const float other);
			friend Vec operator-(const Vec &m, const BaseMat other);
		protected:
		private:
	};
	class Vec2 : public Vec {
		public:
			Vec2();  // 0 0
			Vec2(const Vec2 &vec);
			Vec2(const BaseMat &mat);
			Vec2(std::vector<float> data);
			Vec2(float _x, float _y);
			~Vec2();

			friend Vec2 operator*(const Vec2 &v, const float other);
			friend Vec2 operator+(const Vec2 &m, const float other);
			friend Vec2 operator+(const Vec2 &m, const BaseMat other);
			friend Vec2 operator-(const Vec2 &m, const float other);
			friend Vec2 operator-(const Vec2 &m, const BaseMat other);
		protected:
		private:
	};
	class Vec3 : public Vec {
		public:
			Vec3();  // 0 0 0
			Vec3(const Vec3 &vec);
			Vec3(const Vec4 &vec4);
			Vec3(const BaseMat &mat);
			Vec3(std::vector<float> data);
			Vec3(float _x, float _y, float _z);
			~Vec3();

			Vec3 cross(const Vec3 &v) const;
			float dot(const Vec3 &v) const;

			friend Vec3 operator*(const Vec3 &v, const float other);
			friend Vec3 operator+(const Vec3 &m, const float other);
			friend Vec3 operator+(const Vec3 &m, const BaseMat other);
			friend Vec3 operator-(const Vec3 &m, const float other);
			friend Vec3 operator-(const Vec3 &m, const BaseMat other);
		protected:
		private:
	};
	class Vec4 : public Vec {
		public:
			Vec4();  // 0 0 0 1
			Vec4(const Vec4 &vec);
			Vec4(const Vec3 &vec3);
			Vec4(const BaseMat &mat);
			Vec4(std::vector<float> data);
			Vec4(float _x, float _y, float _z, float _w=1);
			~Vec4();

			friend Vec4 operator*(const Vec4 &v, const float other);
			friend Vec4 operator+(const Vec4 &m, const float other);
			friend Vec4 operator+(const Vec4 &m, const BaseMat other);
			friend Vec4 operator-(const Vec4 &m, const float other);
			friend Vec4 operator-(const Vec4 &m, const BaseMat other);
		protected:
		private:
	};

	class SquareMat : public BaseMat {
		public:
			SquareMat(int size, bool identity=true);
			SquareMat(BaseMat mat);
			SquareMat(int size, std::vector<float> data);
			~SquareMat();

			int getSize() const;

			friend SquareMat operator*(SquareMat m, const float other);
			friend SquareMat operator*(SquareMat m, const BaseMat other);
			friend SquareMat operator+(SquareMat m, const float other);
			friend SquareMat operator+(SquareMat m, const BaseMat other);
			friend SquareMat operator-(SquareMat m, const float other);
			friend SquareMat operator-(SquareMat m, const BaseMat other);
		protected:
		private:
	};
	class Mat2 : public SquareMat {
		public:
			Mat2(bool identity=true);
			Mat2(SquareMat mat);
			Mat2(std::vector<float> data);
			~Mat2();

			friend Mat2 operator*(Mat2 m, const float other);
			friend Mat2 operator*(Mat2 m, const BaseMat other);
			friend Mat2 operator+(Mat2 m, const float other);
			friend Mat2 operator+(Mat2 m, const BaseMat other);
			friend Mat2 operator-(Mat2 m, const float other);
			friend Mat2 operator-(Mat2 m, const BaseMat other);
		protected:
		private:
	};
	class Mat3 : public SquareMat {
		public:
			Mat3(bool identity=true);
			Mat3(SquareMat mat);
			Mat3(std::vector<float> data);
			~Mat3();

			friend Mat3 operator*(Mat3 m, const float other);
			friend Mat3 operator*(Mat3 m, const BaseMat other);
			friend Mat3 operator+(Mat3 m, const float other);
			friend Mat3 operator+(Mat3 m, const BaseMat other);
			friend Mat3 operator-(Mat3 m, const float other);
			friend Mat3 operator-(Mat3 m, const BaseMat other);
		protected:
		private:
	};
	class Mat4 : public SquareMat {
		public:
			Mat4(bool identity=true);
			Mat4(SquareMat mat);
			Mat4(std::vector<float> data);
			~Mat4();

			Mat4 scale(Vec3 val);  // scale martix
			Mat4 scale(float val);  // scale martix
			Mat4 scale(float valX, float valY, float valZ);  // scale martix

			Mat4 translate(Vec3 val);  // translate martix
			Mat4 translate(float valX, float valY, float valZ);  // translate martix

			Mat4 rotateRad(float radians, Vec3 axis);  // rotate around axis
			Mat4 rotateRad(float radians, float axX, float axY, float axZ);  // rotate around axis
			Mat4 rotateDeg(float degrees, Vec3 axis);  // rotate around axis
			Mat4 rotateDeg(float degrees, float axX, float axY, float axZ);  // rotate around axis

			Mat4 lookAt(const Vec3 &src, const Vec3 &dst);  // look at a position
			Mat4 perspective(float fov_y, float aspect, float z_near, float z_far);

			friend Mat4 operator*(Mat4 m, const float other);
			friend Mat4 operator*(Mat4 m, const BaseMat other);
			friend Mat4 operator+(Mat4 m, const float other);
			friend Mat4 operator+(Mat4 m, const BaseMat other);
			friend Mat4 operator-(Mat4 m, const float other);
			friend Mat4 operator-(Mat4 m, const BaseMat other);
		protected:
		private:
	};

	float radians(float deg);
	float degrees(float rad);

	Vec3 normalize(const Vec3 &vec);
	Mat4 lookAt(const Vec3 &src, const Vec3 &dst);
	Vec3 cross(const Vec3 &vec1, const Vec3 &vec2);
	float dot(const Vec3 &vec1, const Vec3 &vec2);
	Mat4 perspective(float fov_y, float aspect, float z_near, float z_far);
}