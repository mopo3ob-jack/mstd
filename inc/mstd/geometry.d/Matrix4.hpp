#ifndef MSTD_MATRIX4_HPP
#define MSTD_MATRIX4_HPP

#include "Matrix.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include <cstring>
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix<T, 4> {
public:
	using Column = Vector<T, 4>;

	constexpr Matrix() {}

	constexpr explicit Matrix(T s) {
		data[0][0] = s;
		data[1][0] = 0;
		data[2][0] = 0;
		data[3][0] = 0;
		data[0][1] = 0;
		data[1][1] = s;
		data[2][1] = 0;
		data[3][1] = 0;
		data[0][2] = 0;
		data[1][2] = 0;
		data[2][2] = s;
		data[3][2] = 0;
		data[0][3] = 0;
		data[1][3] = 0;
		data[2][3] = 0;
		data[3][3] = s;
	}

	template <typename U>
	constexpr explicit Matrix(Matrix<U, 4> m) {
		for (Size i = 0; i < 4; ++i) data[i] = m[i];
	}

	constexpr Matrix(Vector4<T> a, Vector4<T> b, Vector4<T> c, Vector4<T> d) {
		data[0] = a;
		data[1] = b;
		data[2] = c;
		data[3] = d;
	}

	constexpr Matrix(std::initializer_list<Vector4<T>> init) {
		std::copy(data, data + 16, init);
	}

	template <Size N>
	constexpr Matrix operator*(const Matrix<T, N, 4>& m) const {
		Matrix<T, N, 4> result;

		for (Size c = 0; c < 4; ++c) {
			for (Size r = 0; r < 4; ++r) {
				T sum = 0;

				for (Size i = 0; i < N; ++i) {
					sum += data[i][r] * m.data[c][i];
				}

				result.data[c][r] = sum;
			}
		}

		return result;
	}

	constexpr Vector4<T> operator*(Vector4<T> v) const {
		Vector4<T> result;

		result.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.w;
		result.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.w;
		result.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.w;
		result.w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.w;

		return result;
	}

	constexpr Column& operator[](Size i) {
		return data[i];
	}

	constexpr const Column& operator[](Size i) const {
		return data[i];
	}

	constexpr Bool operator==(const Matrix& v) const {
		return std::equal(data, data + 4, v.data);
	}

	constexpr Bool operator!=(const Matrix& v) const {
		return !std::equal(data, data + 4, v.data);
	}

	Column data[4];
};

template <typename T>
static constexpr Matrix<T, 4> perspective(T aspect, T fov, T zNear, T zFar) {
	T length = zFar - zNear;

	return Matrix<T, 4>(
		Vector4<T>(T(1) / (aspect * std::tan(fov / T(2))), T(0), T(0), T(0)),
		Vector4<T>(T(0), T(1) / (std::tan(fov / T(2))), T(0), T(0)),
		Vector4<T>(T(0), T(0), zFar / length, T(1)),
		Vector4<T>(T(0), T(0), -zFar * zNear / length, T(0))
	);
}

template <typename T>
static constexpr Matrix<T, 4> rotateX(T angle) {
	T cosA = std::cos(angle);
	T sinA = std::sin(angle);

	return {
		{1,  0,    0,     0},
		{0,  cosA, -sinA, 0},
		{0,  sinA, cosA,  0},
		{0,  0,    0,     1}
	};
}

template <typename T>
static constexpr Matrix<T, 4> rotateY(T angle) {
	T cosA = std::cos(angle);
	T sinA = std::sin(angle);

	return {
		{cosA,  0, sinA,  0},
		{0,     1, 0,     0},
		{-sinA, 0, cosA,  0},
		{0,     0, 0,     1}
	};
}

template <typename T>
static constexpr Matrix<T, 4> rotateZ(T angle) {
	T cosA = std::cos(angle);
	T sinA = std::sin(angle);

	return {
		{cosA,  -sinA, 0, 0},
		{sinA,  cosA,  0, 0},
		{0,     0,     1, 0},
		{0,     0,     0, 1}
	};
}

template <typename T>
using Matrix4 = Matrix<T, 4>;
using Matrix4f = Matrix4<F32>;
using Matrix4d = Matrix4<F64>;

}

#endif
