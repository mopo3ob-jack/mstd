#ifndef MSTD_ROTOR_HPP
#define MSTD_ROTOR_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
#include <iostream>

namespace mstd {

template <typename T>
class Rotor {
public:
	constexpr Rotor() {
		s = 1.0f;
		yz = 0.0f;
		zx = 0.0f;
		xy = 0.0f;
	}

	constexpr Rotor(T s, T yz, T zx, T xy) {
		this->s = s;
		this->yz = yz;
		this->zx = zx;
		this->xy = xy;
	}

	constexpr Rotor(Vector3<T> from, Vector3<T> to) {
		from = normalize(from);
		to = normalize(to);

		Vector3<T> mid = normalize(from + to);

		Vector3<T> wedge = cross(from, mid);

		s = dot(from, mid);
		yz = wedge.x;
		zx = wedge.y;
		xy = wedge.z;
	}

	constexpr Rotor operator-() const {
		return Rotor(s, -yz, -zx, -xy);
	}

	constexpr operator Matrix3<T>() {
		Vector4<T> x(s, -xy, zx, yz);
		Vector4<T> y(xy, s, -yz, zx);
		Vector4<T> z(-zx, yz, s, xy);

		auto sandwich = [&](Vector4<T> c) {
			return Vector3<T>(
				c.x * s + c.y * xy - c.z * zx + c.w * yz,
				-c.x * xy + c.y * s + c.z * yz + c.w * zx,
				c.x * zx - c.y * yz + c.z * s + c.w * xy
			);
		};

		return {
			sandwich(x),
			sandwich(y),
			sandwich(z)
		};
	}

	T s, yz, zx, xy;
};

using Rotorf = Rotor<F32>;
using Rotord = Rotor<F64>;

}

#endif
