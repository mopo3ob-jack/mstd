#ifndef MSTD_MATRIX3_HPP
#define MSTD_MATRIX3_HPP

#include "Matrix.hpp"
#include "Vector3.hpp"
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix<T, 3> {
public:
	using Column = Vector<T, 3>;

	constexpr Matrix() {}

	constexpr explicit Matrix(T s) {
		data[0][0] = s;
		data[1][0] = 0;
		data[2][0] = 0;
		data[0][1] = 0;
		data[1][1] = s;
		data[2][1] = 0;
		data[0][2] = 0;
		data[1][2] = 0;
		data[2][2] = s;
	}

	constexpr Matrix(std::initializer_list<Vector3<T>> init) {
		std::copy(data, data + 9, init);
	}

	template <Size N>
	constexpr Matrix operator*(const Matrix<T, N, 3>& m) const {
		Matrix<T, N, 3> result;

		for (Size c = 0; c < 3; ++c) {
			for (Size r = 0; r < 3; ++r) {
				T sum = 0;

				for (Size i = 0; i < N; ++i) {
					sum += data[i][r] * m.data[c][i];
				}

				result.data[c][r] = sum;
			}
		}

		return result;
	}

	constexpr Vector3<T> operator*(Vector3<T> v) const {
		Vector3<T> result;

		result.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z;
		result.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z;
		result.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z;

		return result;
	}

	constexpr Column& operator[](Size i) {
		return data[i];
	}

	constexpr const Column& operator[](Size i) const {
		return data[i];
	}

	constexpr Bool operator==(const Matrix& v) const {
		return std::equal(data, data + 3, v.data);
	}

	constexpr Bool operator!=(const Matrix& v) const {
		return !std::equal(data, data + 3, v.data);
	}

	Column data[3];
};

template <typename T>
using Matrix3 = Matrix<T, 3>;
using Matrix3f = Matrix3<F32>;
using Matrix3d = Matrix3<F64>;

}

#endif
