#ifndef MSTD_VECTOR4_HPP
#define MSTD_VECTOR4_HPP

#include "../misc.d/primitive.h"
#include <string>
#include <cmath>

namespace mstd {

template <typename T>
class Vector4 {
public:
	constexpr Vector4() {}

	constexpr Vector4(T s) {
		x = s;
		y = s;
		z = s;
		w = s;
	}

	constexpr Vector4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	constexpr Vector4 operator+(const Vector4& v) const {
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	constexpr Vector4 operator-(const Vector4& v) const {
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	constexpr Vector4 operator*(T s) const {
		return Vector4(x * s, y * s, z * s, w * s);
	}

	constexpr Vector4 operator/(T s) const { \
		return Vector4(x / s, y / s, z / s, w / s);
	}

	constexpr Vector4 operator+=(const Vector4& v) {
		return *this = *this + v;
	}

	constexpr Vector4 operator-=(const Vector4& v) {
		return *this = *this - v;
	}

	constexpr Vector4 operator*=(T s) {
		return *this = *this * s;
	}

	constexpr Vector4 operator/=(T s) {
		return *this = *this / s;
	}

	constexpr T dot(const Vector4& v) const {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	constexpr T magnitude() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	constexpr Vector4 normalized() const {
		T invLength = 1.0f / std::sqrt(x * x + y * y + z * z + w * w);

		return *this * invLength;
	}

	constexpr Vector4 normalize() {
		T invLength = 1.0f / std::sqrt(x * x + y * y + z * z + w * w);

		return *this *= invLength;
	}

	constexpr Vector4 reflect(const Vector4& v) const {
		return v - (2 * dot(v) * *this);
	}

	constexpr operator std::string() const {
		std::string result;
		result.reserve(48);

		result.push_back('<');
		result += std::to_string(x);
		result.push_back(',');
		result += std::to_string(y);
		result.push_back(',');
		result += std::to_string(z);
		result.push_back(',');
		result += std::to_string(w);
		result.push_back('>');
		return result;
	}

	union {
		struct {
			T x, y, z, w;
		};
		struct {
			T i, j, k;
		};
		struct {
			T r, g, b, a;
		};
	};
};

template <typename T>
constexpr Vector4<T> operator*(T s, Vector4<T> v) {
	return Vector4(s * v.x, s * v.y, s * v.z, s * v.w);
}

template <typename T>
constexpr Vector4<T> operator/(T s, Vector4<T> v) {
	return Vector4(s / v.x, s / v.y, s / v.z, s / v.w);
}

template <>
constexpr inline Vector4<F32> Vector4<F32>::operator/(F32 s) const {
	F32 is = 1.0f / s;
	return Vector4(x * is, y * is, z * is, w * is);
}

template <>
constexpr inline Vector4<F64> Vector4<F64>::operator/(F64 s) const {
	F64 is = 1.0f / s;
	return Vector4(x * is, y * is, z * is, w *  is);
}

typedef Vector4<F32> Vector4f;
typedef Vector4<F64> Vector4d;

}

#endif
