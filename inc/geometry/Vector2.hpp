#ifndef MSTD_VECTOR2_HPP
#define MSTD_VECTOR2_HPP

#include "../misc/primitive.h"
#include <string>
#include <cmath>

namespace mstd {

template <typename T>
class Vector2 {
public:
	constexpr Vector2() {}

	constexpr Vector2(T s) {
		x = s;
		y = s;
	}

	constexpr Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}

	constexpr Vector2(const Vector2& v) {
		this->x = v.x;
		this->y = v.y;
	}

	constexpr Vector2 operator=(const Vector2& v) {
		this->x = v.x;
		this->y = v.y;

		return *this;
	}

	constexpr Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	constexpr Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	constexpr Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	constexpr Vector2 operator*(T s) const {
		return Vector2(x * s, y * s);
	}

	constexpr Vector2 operator/(T s) const { \
		return Vector2(x / s, y / s);
	}

	constexpr Vector2 operator+=(const Vector2& v) {
		return Vector2(x += v.x, y += v.y);
	}

	constexpr Vector2 operator-=(const Vector2& v) {
		return Vector2(x -= v.x, y -= v.y);
	}

	constexpr Vector2 operator*=(T s) {
		return Vector2(x *= s, y *= s);
	}

	constexpr Vector2 operator/=(T s) {
		return Vector2(x /= s, y /= s);
	}

	constexpr T dot(const Vector2& v) const {
		return x * v.x + y * v.y;
	}

	constexpr T cross(const Vector2& v) const {
		return x * v.x + y * v.y;
	}

	constexpr T magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	constexpr Vector2 normalized() const {
		T invLength = 1.0f / std::sqrt(x * x + y * y);

		return *this * invLength;
	}

	constexpr Vector2 normalize() {
		T invLength = 1.0f / std::sqrt(x * x + y * y);

		return *this *= invLength;
	}

	constexpr Vector2 reflect(const Vector2& v) const {
		return v - (2 * dot(v) * *this);
	}

	constexpr operator std::string() const {
		std::string result;
		result.reserve(32);

		result.push_back('<');
		result += std::to_string(x);
		result.push_back(',');
		result += std::to_string(y);
		result.push_back('>');
		return result;
	}

	union {
		struct {
			T x, y;
		};
		struct {
			T u, v;
		};
		struct {
			T i, j;
		};
		struct {
			T w, h;
		};
	};
};

template <typename T>
constexpr Vector2<T> operator*(T s, Vector2<T> v) {
	return Vector2(s * v.x, s * v.y);
}

template <typename T>
constexpr Vector2<T> operator/(T s, Vector2<T> v) {
	return Vector2(s / v.x, s / v.y);
}

typedef Vector2<F32> Vector2f;
typedef Vector2<F64> Vector2d;

}

#endif
