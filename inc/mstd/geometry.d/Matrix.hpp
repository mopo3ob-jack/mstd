#ifndef MSTD_MATRIX_HPP
#define MSTD_MATRIX_HPP

#include "Vector.hpp"
#include <string>

namespace mstd {

template <typename T, Size R, Size C>
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
	constexpr Matrix operator*(const Matrix<T, C, N>& m) const {
		Matrix<T, R, N> result;

		if constexpr (R * N > 1024) {
			Matrix<T, C, N> t = m.transpose();

			for (Size c = 0; c < 4; ++c) {
				for (Size r = 0; r < 4; ++r) {
					T sum = 0;

					for (Size i = 0; i < 4; ++i) {
						sum += data[r][i] * t.data[c][i];
					}

					result.data[r][c] = sum;
				}
			}
		} else {
			for (Size c = 0; c < 4; ++c) {
				for (Size r = 0; r < 4; ++r) {
					T sum = 0;

					for (Size i = 0; i < 4; ++i) {
						sum += data[r][i] * m.data[i][c];
					}

					result.data[r][c] = sum;
				}
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

private:
	Column data[C];
};

}

#endif
