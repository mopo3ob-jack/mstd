#ifndef MSTD_VECTOR4_HPP
#define MSTD_VECTOR4_HPP

#include "Vector.hpp"

namespace mstd {

template <typename T>
class Vector<T, 4> {
public:
	constexpr Vector() {}

	constexpr explicit Vector(T s) {
		x = s;
		y = s;
		z = s;
		w = s;
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
		&& (totalArgSize<Args...> == 4)
	)
	constexpr Vector(Args&&... args) {
		Size index = 0;
		(append(index, std::forward<Args>(args)), ...);
	}

	constexpr Vector operator*(T s) const {
		return Vector(x * s, y * s, z * s, w * s);
	}

	constexpr Vector operator/(T s) const {
		return Vector(x / s, y / s, z / s, w / s);
	}
	
	constexpr Vector& operator*=(T s) {
		x *= s; y *= s; z *= s; w *= s;
		return *this;
	}

	constexpr Vector& operator/=(T s) {
		x /= s; y /= s; z /= s; w *= s;
		return *this;
	}

	constexpr Vector operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	constexpr Vector operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	constexpr Vector operator*(const Vector& v) const {
		return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	constexpr Vector operator/(const Vector& v) const {
		return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	constexpr Vector operator-() const {
		return Vector(-x, -y, -z);
	}

	constexpr Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	constexpr Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}

	constexpr Vector& operator*=(const Vector& v) {
		x *= v.x; y *= v.y; z *= v.z; w *= v.w;
		return *this;
	}

	constexpr Vector& operator/=(const Vector& v) {
		x /= v.x; y /= v.y; z /= v.z; w /= v.w;
		return *this;
	}

	constexpr T& operator[](Size i) {
		return data[i];
	}

	constexpr const T& operator[](Size i) const {
		return data[i];
	}

	constexpr Bool operator==(const Vector& v) const {
		return data == v.data;
	}

	constexpr operator std::string() const {
		std::string result;
		std::string first = std::to_string(data[0]);
		result.reserve(4 * (first.size() + 1) + 2);
		result.push_back('<');
		result += first;
		for (Size i = 1; i < 4; ++i) {
			result.push_back(',');
			result += std::move(std::to_string(data[i]));
		}
		result.push_back('>');

		return result;
	}

	union {
		std::array<T, 4> data;
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
using Vector4 = Vector<T, 4>;
using Vector4f = Vector4<F32>;
using Vector4d = Vector4<F64>;

}

#endif
