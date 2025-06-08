#ifndef MSTD_VECTOR3_HPP
#define MSTD_VECTOR3_HPP

#include "Vector.hpp"

namespace mstd {

template <typename T>
class Vector<T, 3> {
public:
	constexpr Vector() {}

	constexpr explicit Vector(T s) {
		x = s;
		y = s;
		z = s;
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
		&& (totalArgSize<Args...> == 3)
	)
	constexpr Vector(Args&&... args) {
		Size index = 0;
		(append(index, std::forward<Args>(args)), ...);
	}

	constexpr Vector operator*(T s) const {
		return Vector(x * s, y * s, z * s);
	}

	constexpr Vector operator/(T s) const {
		return Vector(x / s, y / s, z / s);
	}
	
	constexpr Vector& operator*=(T s) {
		x *= s; y *= s; z *= s;
		return *this;
	}

	constexpr Vector& operator/=(T s) {
		x /= s; y /= s; z /= s;
		return *this;
	}

	constexpr Vector operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	constexpr Vector operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	constexpr Vector operator*(const Vector& v) const {
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	constexpr Vector operator/(const Vector& v) const {
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	constexpr Vector operator-() const {
		return Vector(-x, -y, -z);
	}

	constexpr Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	constexpr Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	constexpr Vector& operator*=(const Vector& v) {
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	constexpr Vector& operator/=(const Vector& v) {
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	constexpr T& operator[](Size i) {
		return data[i];
	}

	constexpr const T& operator[](Size i) const {
		return data[i];
	}

	constexpr operator std::string() const {
		std::string result;
		std::string first = std::to_string(data[0]);
		result.reserve(3 * (first.size() + 1) + 2);
		result.push_back('<');
		result += first;
		for (Size i = 1; i < 3; ++i) {
			result.push_back(',');
			result += std::move(std::to_string(data[i]));
		}
		result.push_back('>');

		return result;
	}

	union {
		T data[3];
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
constexpr Vector<T, 3> cross(const Vector<T, 3>& a, const Vector<T, 3>& b) {
	return Vector<T, 3>(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

template <typename T>
using Vector3 = Vector<T, 3>;
using Vector3f = Vector3<F32>;
using Vector3d = Vector3<F64>;

}

#endif
