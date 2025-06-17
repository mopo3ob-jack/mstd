#ifndef MSTD_MATRIX2_HPP
#define MSTD_MATRIX2_HPP

#include "Matrix.hpp"
#include "Vector2.hpp"
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix<T, 2> {
public:
	using Column = Vector<T, 2>;

	constexpr Matrix() {}

	constexpr explicit Matrix(T s) {
		data[0][0] = s;
		data[1][0] = 0;
		data[1][1] = s;
		data[0][1] = 0;
	}

	constexpr Matrix(std::initializer_list<Vector2<T>> init) {
		std::copy(data, data + 4, init);
	}

	template <Size N>
	constexpr Matrix operator*(const Matrix<T, N, 2>& m) const {
		Matrix<T, N, 4> result;

		for (Size c = 0; c < 2; ++c) {
			for (Size r = 0; r < 2; ++r) {
				T sum = 0;

				for (Size i = 0; i < N; ++i) {
					sum += data[i][r] * m.data[c][i];
				}

				result.data[c][r] = sum;
			}
		}

		return result;
	}

	constexpr Vector<T, 2> operator*(Vector2<T> v) const {
		Vector<T, 2> result;

		result.x = data[0][0] * v.x + data[0][1] * v.y;
		result.y = data[1][0] * v.y + data[1][1] * v.y;

		return result;
	}

	constexpr Column& operator[](Size i) {
		return data[i];
	}

	constexpr const Column& operator[](Size i) const {
		return data[i];
	}

	static constexpr Matrix rotateZ(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{cosA,  -sinA},
			{sinA,  cosA},
		};
	}

	std::array<Column, 2> data;
};

template <typename T>
using Matrix2 = Matrix<T, 2>;
using Matrix2f = Matrix2<F32>;
using Matrix2d = Matrix2<F32>;

}

#endif
