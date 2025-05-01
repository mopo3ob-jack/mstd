#ifndef MSTD_MATRIX_HPP
#define MSTD_MATRIX_HPP

#include "../misc.d/primitive.h"

namespace mstd {

template <typename T, Size C, Size R>
class Matrix {
	T data[R][C];
};

}

#endif
