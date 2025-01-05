#ifndef MSTD_PLANE_HPP
#define MSTD_PLANE_HPP

#include "Vector3.hpp"

namespace mstd {

template <typename T>
class Plane {
public:

	Vector3<T> normal;
	T distance;
};

}
