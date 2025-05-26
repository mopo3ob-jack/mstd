#ifndef MSTD_ROTOR_HPP
#define MSTD_ROTOR_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

namespace mstd {

template <typename T>
class Rotor {
public:
	constexpr Rotor() {
		this->w = 1.0;
		this->yz = 0.0;
		this->zx = 0.0;
		this->xy = 0.0;
	}

	constexpr Rotor(T w, T yz, T zx, T xy) {
		this->w = w;
		this->yz = yz;
		this->zx = zx;
		this->xy = xy;
	}

	constexpr Rotor(Vector3<T> a, Vector3<T> b) {
		Vector3<T> wedge = cross(b, a);

		yz = wedge.x;
		zx = wedge.y;
		xy = wedge.z;

		w = dot(a, b);
	}

	constexpr Rotor operator+(const Rotor& r) const {
		return {
			w * r.w - yz * r.yz - zx * r.zx - xy * r.xy,
			w * r.yz + xy * r.zx - zx * r.xy + yz * r.w,
			w * r.zx + yz * r.xy - xy * r.yz + zx * r.w,
			w * r.xy + zx * r.yz - yz * r.zx + xy * r.w
		};
	}

	constexpr Rotor operator-(const Rotor& r) const {
		return {
			w * r.w - yz * r.yz - zx * r.zx - xy * r.xy,
			w * r.yz + xy * r.zx - zx * r.xy + yz * r.w,
			w * r.zx + yz * r.xy - xy * r.yz + zx * r.w,
			w * r.xy + zx * r.yz - yz * r.zx + xy * r.w
		};
	}

	constexpr Rotor operator-() const {
		return {
			w,
			-yz,
			-zx,
			-xy
		};
	}

	constexpr Rotor operator+=(const Rotor& v) {
		return *this = *this + v;
	}

	constexpr Rotor operator-=(const Rotor& v) {
		return *this = *this - v;
	}

	constexpr Vector3<T> rotate(const Vector3<T>& v) const {
		T tx = w * v.x + xy * v.y - zx * v.z;
		T ty = w * v.y + yz * v.z - xy * v.x;
		T tz = w * v.z + zx * v.x - yz * v.y;
		T txyz = yz * v.x + zx * v.y + xy * v.z;

		return {
			w * tx + xy * ty + yz * txyz - zx * tz,
			w * ty + yz * tz + zx * txyz - xy * tx,
			w * tz + zx * tx + xy * txyz - yz * ty,
		};
	}

	constexpr operator std::string() const {
		std::string result;
		result.reserve(48);

		result.push_back('<');
		result += std::to_string(w);
		result.push_back(',');
		result += std::to_string(yz);
		result.push_back(',');
		result += std::to_string(zx);
		result.push_back(',');
		result += std::to_string(xy);
		result.push_back('>');
		return result;
	}

	constexpr operator Matrix3<T>() const {
		auto transform = [this](Vector3<T> data, T tx, T ty, T tz, T txyz) {
			data[0] = w * tx + xy * ty + yz * txyz - zx * tz;
			data[1] = w * ty + yz * tz + zx * txyz - xy * tx;
			data[2] = w * tz + zx * tx + xy * txyz - yz * ty;
		};

		Matrix3<T> result;
		transform(result.data[0], w, -xy, zx, yz);
		transform(result.data[1], xy, w, -yz, zx);
		transform(result.data[2], -zx, yz, w, xy);

		return result;
	}

	constexpr operator Matrix4<T>() const {
		auto transform = [this](Vector4<T> data, T tx, T ty, T tz, T txyz) {
			data[0] = w * tx + xy * ty + yz * txyz - zx * tz;
			data[1] = w * ty + yz * tz + zx * txyz - xy * tx;
			data[2] = w * tz + zx * tx + xy * txyz - yz * ty;
			data[3] = 0;
		};

		Matrix4<T> result;
		transform(result.data[0], w, -xy, zx, yz);
		transform(result.data[1], xy, w, -yz, zx);
		transform(result.data[2], -zx, yz, w, xy);
		result.data[3][0] = 0.0;
		result.data[3][1] = 0.0;
		result.data[3][2] = 0.0;
		result.data[3][3] = 1.0;

		return result;
	}

	T yz, zx, xy, w;
};

using Rotorf = Rotor<F32>;
using Rotord = Rotor<F64>;

}

#endif
