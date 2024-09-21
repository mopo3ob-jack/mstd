#ifndef MSTD_MATRIX_HPP
#define MSTD_MATRIX_HPP

#include "../primitive.h"

namespace mstd {

template <Size columns, Size rows, typename T>
class Matrix {
public:
	constexpr Matrix() {}

	constexpr Matrix(T s) {
		for (Size x = 0; x < columns; ++x) {
			for (Size y = 0; y < columns; ++y) {
				data[x][y] = x == y ? s : 0.0;
			}
		}
	}

	template <Size argCols, Size argRows>
	Matrix<rows, argCols, T> operator*(Matrix<argCols, argRows, T> m) {
	}

	T data[columns][rows];
};

}

#endif
