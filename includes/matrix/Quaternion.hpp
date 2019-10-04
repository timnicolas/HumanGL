#pragma once

#include "Matrix.hpp"

namespace mat {
	class Quaternion {
		public:
			Quaternion();
			Quaternion(const Vec3 &v, float degrees);

			const Quaternion inverted() const;
			const Quaternion operator*(const Quaternion &q) const;
			const Vec3 operator*(const Vec3 &other) const;
			const Quaternion operator^(float t) const;
			const Quaternion slerp(const Quaternion &r, float t) const;

			void toAxisAngle(Vec3 &vecAxis, float &flAngle) const;

			Vec3 vec;  // x, y, z
			float w;
		protected:
		private:
	};
}