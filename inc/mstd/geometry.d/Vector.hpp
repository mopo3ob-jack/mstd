#ifndef MSTD_VECTOR_HPP
#define MSTD_VECTOR_HPP

#include "../misc.d/primitive.h"
#include "../misc.d/errorText.h"
#include <initializer_list>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>

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
	template <typename U>
	static constexpr Size size = 1;

	template <typename U, Size S>
	static constexpr Size size<Vector<U, S>> = S;

	template <typename... Args>
	static constexpr Size totalArgSize = (size<std::decay_t<Args>> + ... + 0);

	constexpr Vector() {}

	constexpr Vector(T s) {
		for (Size i = 0; i < R; ++i) data[i] = s;
	}
	
	template <typename... Args>
	requires (
		((std::is_convertible_v<std::decay_t<Args>, T> || VectorType<std::decay_t<Args>>) && ...)
		&& (totalArgSize<Args...> == R)
	)
	constexpr Vector(Args&&... args) {
		Size index = 0;
		(append(index, std::forward<Args>(args)), ...);
	}

	constexpr Vector& operator=(T s) {
		for (Size i = 0; i < R; ++i) data[i] = s;
		return *this;
	}

	constexpr Vector& operator=(std::initializer_list<T> l) {
		if (l.size() != R) {
			std::cerr << errorText << "";
		}
		for (Size i = 0; i < l.size(); ++i) data[i] = l[i];
		return *this;
	}

	constexpr Vector operator+(T s) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] + s;
		return result;
	}

	constexpr Vector operator-(T s) const {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] - s;
		return result;
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

	constexpr Vector operator+=(T s) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] += s;
		return result;
	}

	constexpr Vector operator-=(T s) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] -= s;
		return result;
	}

	constexpr Vector operator*=(T s) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] *= s;
		return result;
	}
	
	constexpr Vector operator/=(T s) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] /= s;
		return result;
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

	constexpr T dot(Vector v) const {
		T result = 0;
		for (Size i = 0; i < R; ++i) result += data[i] * v.data[i];
		return result;
	}

	constexpr T magnitudeSq() const {
		T result = 0;
		for (Size i = 0; i < R; ++i) result += data[i] * data[i];
		return result;
	}

	constexpr T magnitude() const {
		return std::sqrt(magnitudeSq());
	}

	constexpr T& operator[](Size i) {
		return data[i];
	}

	constexpr operator std::string() const {
		std::string result;
		std::string first(data[0]);
		result.reserve(R * (first.size() + 1) + 2);
		result.push_back('<');
		for (Size i = 1; i < R; ++i) {
			result.push_back(',');
			result += std::move(std::string(data[0]));
		}
		result.push_back('>');

		return result;
	}

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

	T data[R];
};

}

#endif
