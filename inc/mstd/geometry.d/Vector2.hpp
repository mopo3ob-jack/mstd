#ifndef MSTD_VECTOR2_HPP
#define MSTD_VECTOR2_HPP

#include "Vector.hpp"

namespace mstd {

template <typename T>
class Vector<T, 2> {
public:
	constexpr Vector() {}

	constexpr explicit Vector(T s) {
		x = s;
		y = s;
	}

	template <typename U>
	static constexpr Size size = 1;

	template <typename U, Size S>
	static constexpr Size size<Vector<U, S>> = S;

	template <typename... Args>
	static constexpr Size totalArgSize = (size<std::decay_t<Args>> + ... + 0);
	
	template <typename... Args>
	requires (
		((std::is_convertible_v<std::decay_t<Args>, T> || VectorType<std::decay_t<Args>>) && ...)
		&& (totalArgSize<Args...> == 2)
	)
	constexpr Vector(Args&&... args) {
		Size index = 0;
		(append(index, std::forward<Args>(args)), ...);
	}

	constexpr Vector operator*(T s) const {
		return Vector(x * s, y * s);
	}

	constexpr Vector operator/(T s) const {
		return Vector(x / s, y / s);
	}
	
	constexpr Vector& operator*=(T s) {
		x *= s; y *= s;
		return *this;
	}

	constexpr Vector& operator/=(T s) {
		x /= s; y /= s;
		return *this;
	}

	constexpr Vector operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y);
	}

	constexpr Vector operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y);
	}

	constexpr Vector operator*(const Vector& v) const {
		return Vector(x * v.x, y * v.y);
	}

	constexpr Vector operator/(const Vector& v) const {
		return Vector(x / v.x, y / v.y);
	}

	constexpr Vector operator-() const {
		return Vector(-x, -y);
	}

	constexpr Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y;
		return *this;
	}

	constexpr Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y;
		return *this;
	}

	constexpr Vector& operator*=(const Vector& v) {
		x *= v.x; y *= v.y;
		return *this;
	}

	constexpr Vector& operator/=(const Vector& v) {
		x /= v.x; y /= v.y;
		return *this;
	}

	constexpr T& operator[](Size i) {
		return data[i];
	}

	constexpr const T& operator[](Size i) const {
		return data[i];
	}

	constexpr Bool operator==(const Vector& v) const {
		return std::equal(data, data + 2, v.data);
	}

	constexpr Bool operator!=(const Vector& v) const {
		return !std::equal(data, data + 2, v.data);
	}

	constexpr operator std::string() const {
		std::string result;
		std::string first = std::to_string(data[0]);
		result.reserve(2 * (first.size() + 1) + 2);
		result.push_back('<');
		result += first;
		for (Size i = 1; i < 2; ++i) {
			result.push_back(',');
			result += std::move(std::to_string(data[i]));
		}
		result.push_back('>');

		return result;
	}

	union {
		T data[2];
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
		struct {
			T r, g;
		};
	};

private:
	constexpr void append(Size& index, const T& arg) {
		data[index++] = arg;
	}

	template <Size S>
	constexpr void append(Size& index, const Vector<T, S>& arg) {
		for (Size i = 0; i < S; ++i) {
			data[index++] = arg[i];
		}
	}
};

template <typename T>
constexpr T cross(const Vector<T, 2>& a, const Vector<T, 2>& b) {
	return a.x * b.y - a.y * b.x;
}

template <typename T>
using Vector2 = Vector<T, 2>;
using Vector2f = Vector2<F32>;
using Vector2d = Vector2<F64>;

}

#endif
