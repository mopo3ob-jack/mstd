#ifndef MSTD_MATRIX2_HPP
#define MSTD_MATRIX2_HPP

#include "Matrix.hpp"
#include "Vector2.hpp"
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix<T, 2> {
public:
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

	constexpr Matrix operator*(Matrix m) {
		Matrix result;

		for (U32 y = 0; y < 2; ++y) {
			for (U32 x = 0; x < 2; ++x) {
				T sum = 0;

				for (U32 i = 0; i < 2; ++i) {
					sum += data[y][i] * m.data[i][x];
				}

				result.data[y][x] = sum;
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

	constexpr T* operator[](Size i) {
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

	T data[2][2];
};

template <typename T>
using Matrix2 = Matrix<T, 2>;
using Matrix2f = Matrix2<F32>;
using Matrix2d = Matrix2<F32>;

}

#endif
