#ifndef MSTD_ROTOR_HPP
#define MSTD_ROTOR_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"

namespace mstd {

template <typename T>
class Rotor {
public:
	constexpr Rotor(T w, T yz, T zx, T xy) {
		this->w = w;
		this->yz = yz ;
		this->zx = zx;
		this->xy = xy;
	}

	constexpr Rotor(Vector3<T> a, Vector3<T> b) {
		Vector3<T> wedge = b.cross(a);

		yz = wedge.x;
		zx = wedge.y;
		xy = wedge.z;

		w = a.dot(b);
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

	T yz, zx, xy, w;
};

typedef Rotor<F32> Rotorf;
typedef Rotor<F64> Rotord;

}

#endif
