#ifndef MSTD_MATRIX3_HPP
#define MSTD_MATRIX3_HPP

#include "../misc.d/primitive.h"
#include "Vector3.hpp"
#include <cstring>
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix3 {
public:
	constexpr Matrix3() {}

	constexpr explicit Matrix3(T s) {
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

	constexpr Matrix3(std::initializer_list<Vector3<T>> init) {
		std::memcpy(data, init.begin(), sizeof(T) * 9);
	}

	constexpr Matrix3 operator*(Matrix3 m) {
		Matrix3 result;

		for (U32 y = 0; y < 3; ++y) {
			for (U32 x = 0; x < 3; ++x) {
				T sum = 0;

				for (U32 i = 0; i < 2; ++i) {
					sum += data[y][i] * m.data[i][x];
				}

				result.data[y][x] = sum;
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

	constexpr T* operator[](Size i) {
		return data[i];
	}

	static constexpr Matrix3 rotateX(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{1,  0,    0},
			{0,  cosA, -sinA},
			{0,  sinA, cosA},
		};
	}

	static constexpr Matrix3 rotateY(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{cosA,  0, sinA},
			{0,     1, 0},
			{-sinA, 0, cosA},
		};
	}

	static constexpr Matrix3 rotateZ(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{cosA,  -sinA, 1},
			{sinA,  cosA,  0},
			{0,     0,     1},
		};
	}

	T data[3][3];
};

typedef Matrix3<F32> Matrix3f;
typedef Matrix3<F64> Matrix3d;

}

#endif
