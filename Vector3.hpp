#ifndef MSTD_VECTOR3_HPP
#define MSTD_VECTOR3_HPP

#include "primitive.h"
#include <string>
#include <cmath>

namespace mstd {

template <typename T>
class Vector3 {
public:
	constexpr Vector3() {}

	constexpr Vector3(T s) {
		x = s;
		y = s;
		z = s;
	}

	constexpr Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	constexpr Vector3(const Vector3& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	constexpr Vector3 operator=(const Vector3& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;

		return *this;
	}

	constexpr Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	constexpr Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	constexpr Vector3 operator*(T s) const {
		return Vector3(x * s, y * s, z * s);
	}

	constexpr Vector3 operator/(T s) const { \
		return Vector3(x / s, y / s, z / s);
	}

	constexpr Vector3 operator+=(const Vector3& v) {
		return *this = *this + v;
	}

	constexpr Vector3 operator-=(const Vector3& v) {
		return *this = *this - v;
	}

	constexpr Vector3 operator*=(T s) {
		return *this = *this * s;
	}

	constexpr Vector3 operator/=(T s) {
		return *this = *this / s;
	}

	constexpr T dot(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	constexpr Vector3 cross(const Vector3& v) const {
		return Vector3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	constexpr T length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	constexpr Vector3 normalized() const {
		T invLength = 1.0f / std::sqrt(x * x + y * y + z * z);

		return *this * invLength;
	}

	constexpr Vector3 normalize() {
		T invLength = 1.0f / std::sqrt(x * x + y * y + z * z);

		return *this *= invLength;
	}

	constexpr operator std::string() {
		std::string result;
		result.reserve(48);

		result.push_back('<');
		result += std::to_string(x);
		result.push_back(',');
		result += std::to_string(y);
		result.push_back(',');
		result += std::to_string(z);
		result.push_back('>');
		return result;
	}

	union {
		struct {
			T x, y, z;
		};
		struct {
			T i, j, k;
		};
		struct {
			T r, g, b;
		};
	};
};

template <>
constexpr inline Vector3<F32> Vector3<F32>::operator/(F32 s) const {
	F32 is = 1.0f / s;
	return Vector3(x * is, y * is, z * is);
}

template <>
constexpr inline Vector3<F64> Vector3<F64>::operator/(F64 s) const {
	F64 is = 1.0f / s;
	return Vector3(x * is, y * is, z * is);
}

typedef Vector3<F32> Vector3f;
typedef Vector3<F64> Vector3d;

}

#endif
