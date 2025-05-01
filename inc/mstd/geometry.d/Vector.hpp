#ifndef MSTD_VECTOR_HPP
#define MSTD_VECTOR_HPP

#include "../misc.d/primitive.h"
#include <glm/vec2.hpp>
#include <initializer_list>
#include <utility>
#include <cmath>

namespace mstd {

template <typename T, Size R>
class Vector;

template <typename>
struct IsVector : std::false_type {};

template <typename T, Size R>
struct IsVector<Vector<T, R>> : std::true_type {};

template <typename T>
concept VectorType = IsVector<T>::value;

template <typename T>
constexpr Size vectorSize = 1;

template <typename T, Size R>
constexpr Size vectorSize<Vector<T, R>> = R;

template <typename... Args>
constexpr Size totalArgSize = (vectorSize<std::decay_t<Args>> + ... + 0);

template <typename T, Size R>
class Vector {
public:
	constexpr Vector() {}

	// Constructors
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

	// Copy operators
	constexpr Vector& operator=(T s) {
		for (Size i = 0; i < R; ++i) data[i] = s;
		return *this;
	}

	constexpr Vector& operator=(std::initializer_list<T> l) {
		static_assert(l.size() != R);
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

	constexpr Vector operator+=(const Vector& v) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] += v.data[i];
		return result;
	}

	constexpr Vector operator-=(const Vector& v) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] -= v.data[i];
		return result;
	}

	constexpr Vector operator*=(const Vector& v) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] *= v.data[i];
		return result;
	}
	
	constexpr Vector operator/=(const Vector& v) {
		Vector result;
		for (Size i = 0; i < R; ++i) result[i] = data[i] /= v.data[i];
		return result;
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
	
	static consteval Size size() {
		return R;
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
