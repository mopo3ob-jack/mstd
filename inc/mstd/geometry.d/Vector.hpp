#ifndef MSTD_VECTOR_HPP
#define MSTD_VECTOR_HPP

#include "../misc.d/primitive.h"
#include "../misc.d/errorText.h"
#include <initializer_list>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>

namespace mstd {

template <typename T, Size R>
class Vector;

template <typename>
struct IsVector : std::false_type {};

template <typename T, Size R>
struct IsVector<Vector<T, R>> : std::true_type {};

template <typename T>
concept VectorType = IsVector<T>::value;

template <typename T, Size R>
class Vector {
public:
	constexpr Vector() {}

	constexpr explicit Vector(T s) {
		for (Size i = 0; i < R; ++i) data[i] = s;
	}

	using ComponentType = T;

	template <typename U>
	static constexpr Size size = 1;

	template <typename U, Size S>
	static constexpr Size size<Vector<U, S>> = S;

	template <typename... Args>
	static constexpr Size totalArgSize = (size<std::decay_t<Args>> + ... + 0);

	template <typename... Args>
	requires (
		((std::is_convertible_v<std::decay_t<Args>, T> || VectorType<std::decay_t<Args>>) && ...)
		&& (totalArgSize<Args...> == R)
	)
	constexpr Vector(Args&&... args) {
		Size index = 0;
		(append(index, std::forward<Args>(args)), ...);
	}

	constexpr Vector operator*(T s) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] * s;
		return result;
	}
	
	constexpr Vector operator/(T s) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] / s;
		return result;
	}

	constexpr Vector& operator*=(T s) {
		for (Size i = 0; i < R; ++i) data[i] *= s;
		return *this;
	}
	
	constexpr Vector& operator/=(T s) {
		for (Size i = 0; i < R; ++i) data[i] /= s;
		return *this;
	}

	constexpr Vector operator+(const Vector& v) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] + v.data[i];
		return result;
	}

	constexpr Vector operator-(const Vector& v) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] - v.data[i];
		return result;
	}

	constexpr Vector operator*(const Vector& v) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] * v.data[i];
		return result;
	}
	
	constexpr Vector operator/(const Vector& v) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] / v.data[i];
		return result;
	}

	constexpr Vector operator-() const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = -data[i];
		return result;
	}

	constexpr Vector& operator+=(const Vector& v) {
		for (Size i = 0; i < R; ++i) data[i] += v.data[i];
		return *this;
	}

	constexpr Vector& operator-=(const Vector& v) {
		for (Size i = 0; i < R; ++i) data[i] -= v.data[i];
		return *this;
	}

	constexpr Vector& operator*=(const Vector& v) {
		for (Size i = 0; i < R; ++i) data[i] *= v.data[i];
	}
	
	constexpr Vector& operator/=(const Vector& v) {
		for (Size i = 0; i < R; ++i) data[i] /= v.data[i];
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
		result.reserve(R * (first.size() + 1) + 2);
		result.push_back('<');
		result += first;
		for (Size i = 1; i < R; ++i) {
			result.push_back(',');
			result += std::move(std::to_string(data[i]));
		}
		result.push_back('>');

		return result;
	}

	T data[R];

private:
	constexpr void append(Size& index, const T& arg) {
		data[index++] = arg;
	}

	template <Size S>
	constexpr void append(Size& index, Vector<T, S>& arg) {
		for (Size i = 0; i < S; ++i) {
			data[index++] = arg[i];
		}
	}
};

template <typename T, Size R>
static constexpr Vector<T, R> operator*(T s, const Vector<T, R>& v) {
	return Vector(s * v.x, s * v.y);
}

template <typename T, Size R>
static constexpr Vector<T, R> operator/(T s, const Vector<T, R>& v) {
	return Vector(s / v.x, s / v.y);
}

template <typename T, Size R>
static constexpr T dot(const Vector<T, R>& a, const Vector<T, R>& b) {
	T result = 0;
	for (Size i = 0; i < R; ++i) result += a[i] * b[i];
	return result;
}

template <typename T, Size R>
static constexpr T magnitudeSq(const Vector<T, R>& v) {
	T result = 0;
	for (Size i = 0; i < R; ++i) result += v[i] * v[i];
	return result;
}

template <typename T, Size R>
static constexpr T magnitude(const Vector<T, R>& v) {
	return std::sqrt(magnitudeSq(v));
}
	
template <typename T, Size R>
constexpr Vector<T, R> normalize(const Vector<T, R>& v) {
	return v / magnitude(v);
}

template <typename T, Size R>
constexpr Vector<T, R> reflect(const Vector<T, R>& v, const Vector<T, R>& n) {
	return v - T(2) * dot(v, n) * n;
}

}

#endif
