#ifndef MSTD_MATRIX4_HPP
#define MSTD_MATRIX4_HPP

#include "../misc/primitive.h"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include <cstring>
#include <initializer_list>

namespace mstd {

template <typename T>
class Matrix4 {
public:
	constexpr Matrix4() {}

	constexpr Matrix4(T s) {
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

	constexpr Matrix4(std::initializer_list<Vector4<T>> init) {
		std::memcpy(data, init.begin(), sizeof(T) * 16);
	}

	constexpr Matrix4 operator*(Matrix4 m) const {
		Matrix4 result;

		for (U32 x = 0; x < 4; ++x) {
			for (U32 y = 0; y < 4; ++y) {
				T sum = 0;

				for (U32 i = 0; i < 4; ++i) {
					sum += data[y][i] * m.data[i][x];
				}

				result.data[y][x] = sum;
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

	static constexpr Matrix4 perspective(T aspect, T fov, T near, T far) {
		T length = far - near;

		return {
			{T(1) / (aspect * std::tan(fov / T(2))), 0, 0, 0},
			{0, T(1) / (std::tan(fov / T(2))), 0, 0},
			{0, 0, (far + near) / length, -2 * far * near / length},
			{0, 0, 1, 0}
		};
	}

	static constexpr Matrix4 rotateX(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{1,  0,    0,     0},
			{0,  cosA, -sinA, 0},
			{0,  sinA, cosA,  0},
			{0,  0,    0,     1}
		};
	}

	static constexpr Matrix4 rotateY(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{cosA,  0, sinA,  0},
			{0,     1, 0,     0},
			{-sinA, 0, cosA,  0},
			{0,     0, 0,     1}
		};
	}

	static constexpr Matrix4 rotateZ(T angle) {
		T cosA = std::cos(angle);
		T sinA = std::sin(angle);

		return {
			{cosA,  -sinA, 1, 0},
			{sinA,  cosA,  0, 0},
			{0,     0,     1, 0},
			{0,     0,     0, 1}
		};
	}

	static constexpr Matrix4 translate(Vector3<T> position) {
		return {
			{1, 0, 0, position.x},
			{0, 1, 0, position.y},
			{0, 0, 1, position.z},
			{0, 0, 0, 1}
		};
	}

	constexpr T* operator[](Size i) {
		return data[i];
	}

	T data[4][4];
};

typedef Matrix4<F32> Matrix4f;
typedef Matrix4<F64> Matrix4d;

}

#endif
