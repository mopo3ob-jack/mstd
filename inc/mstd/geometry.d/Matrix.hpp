#ifndef MSTD_MATRIX_HPP
#define MSTD_MATRIX_HPP

#include "Vector.hpp"
#include <string>

namespace mstd {

template <typename T, Size C, Size R = C>
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

	constexpr Column& operator[](Size i) {
		return data[i];
	}

	constexpr const Column& operator[](Size i) const {
		return data[i];
	}

	constexpr Bool operator==(const Matrix& v) const {
		return std::equal(data, data + C, v.data);
	}

private:
	Column data[C];
};

template <typename T, Size C, Size R = C>
static constexpr Matrix<T, C, R> transpose(const Matrix<T, C, R>& m) {
	Matrix<T, R, C> result;

	for (Size r = 0; r < R; ++r) {
		for (Size c = 0; c < C; ++c) {
			result[c][r] = m[r][c];
		}
	}

	return result;
}

template <typename T, Size S>
static constexpr Matrix<T, S + 1> translate(const Vector<T, S>& position) {
	Matrix<T, S + 1> result;

	for (Size c = 0; c < S; ++c) {
		for (Size r = 0; r < c; ++r) {
			result[c][r] = T(0);
		}
		result[c][c] = T(1);
		for (Size r = c + 1; r < S + 1; ++r) {
			result[c][r] = T(0);
		}
	}

	result[S] = Vector<T, S + 1>(position, 1.0f);

	return result;
}

}

#endif
