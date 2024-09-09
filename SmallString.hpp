#ifndef MSTD_SMALLSTRING_HPP
#define MSTD_SMALLSTRING_HPP

#include "primitive.h"

namespace mstd {

template <typename C = C8>
class SmallString {
public:
private:
	U32 length;
	C8  string[12];
};

}

#endif
