#ifndef MSTD_MATRIX_HPP
#define MSTD_MATRIX_HPP

#include "Vector.hpp"
#include <string>

namespace mstd {

template <typename T, Size C, Size R>
class Matrix {
public:
	using Column = Vector<T, R>;

	constexpr Matrix operator+(const Matrix& m) const {
		Matrix result;
		for (Size i = 0; i < R; ++i) { result[i] = data[i] + m.data[i]; }
		return result;
	}

	constexpr Matrix operator-(const Matrix& m) const {
		Matrix result;
		for (Size i = 0; i < R; ++i) { result[i] = data[i] - m.data[i]; }
		return result;
	}

	template <Size N>
	constexpr Matrix operator*(const Matrix<T, N, C>& m) const {
		Matrix<T, N, R> result;

		for (Size c = 0; c < C; ++c) {
			for (Size r = 0; r < R; ++r) {
				T sum = 0;

				for (Size i = 0; i < N; ++i) {
					sum += data[i][r] * m.data[c][i];
				}

				result.data[c][r] = sum;
			}
		}

		return result;
	}

	constexpr Matrix operator+=(const Matrix& m) {
		return *this;
	}

	constexpr Matrix operator-() const {
		Matrix result;
		for (Size i = 0; i < R; ++i) { result[i] = -data[i]; }
		return result;
	}

	constexpr Matrix<T, C, R> transpose() const {
		Matrix<T, C, R> result;

		for (Size r = 0; r < R; ++r) {
			for (Size c = 0; c < C; ++c) {
				result[c][r] = data[r][c];
			}
		}

		return result;
	}

	constexpr Column& operator[](Size i) {
		return data[i];
	}

	constexpr const Column& operator[](Size i) const {
		return data[i];
	}

private:
	Column data[C];
};

}

#endif
