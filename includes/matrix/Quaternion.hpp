#pragma once

#include "Matrix.hpp"

namespace mat {
	class Quaternion {
		public:
			Quaternion();
			Quaternion(const Vec3 &v, float degrees);

			const Quaternion inverted() const;
			const Quaternion operator*(const Quaternion &q) const;
			const Vec3 operator*(const Vec3 &other) const;  // apply rotation to the vector
			const Vec4 operator*(const Vec4 &other) const;  // apply rotation to the vector
			const Quaternion operator^(float t) const;
			const Quaternion slerp(const Quaternion &to, float step) const;  // get a point btw this and to (with t btw 0 & 1)

			void toAxisAngle(Vec3 &vecAxis, float &flAngle) const;

			/* operators */
			friend std::ostream &operator<<(std::ostream &out, const Quaternion &q);

			Vec3 vec;  // x, y, z
			float w;
		protected:
		private:
	};
}