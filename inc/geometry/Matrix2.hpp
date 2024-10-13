#ifndef MSTD_MATRIX2_HPP
#define MSTD_MATRIX2_HPP

#include "../primitive.h"
#include "Vector2.hpp"
#include <cstring>
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix2 {
public:
	constexpr Matrix2() {}

	constexpr Matrix2(T s) {
		data[0][0] = s;
		data[1][0] = 0;
		data[1][1] = s;
		data[0][1] = 0;
	}

	constexpr Matrix2(std::initializer_list<Vector2<T>> init) {
		std::memcpy(data, init.begin(), sizeof(T) * 4);
	}

	constexpr Matrix2 operator*(Matrix2 m) {
		Matrix2 result;

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

	constexpr Vector2<T> operator*(Vector2<T> v) const {
		Vector2<T> result;

		result.x = data[0][0] * v.x + data[0][1] * v.y;
		result.y = data[1][0] * v.y + data[1][1] * v.y;

		return result;
	}

	constexpr T* operator[](Size i) {
		return data[i];
	}

	T data[2][2];
};

typedef Matrix2<F32> Matrix2f;
typedef Matrix2<F64> Matrix2d;

}

#endif
