#ifndef MSTD_MEMORY_HPP
#define MSTD_MEMORY_HPP

#include "../primitive.h"

#include <cstdlib>

namespace mstd {

template <typename T>
static inline T* alloc(Size count, Size alignment = alignof(T)) {
	return (T*)std::aligned_alloc(alignment, count * sizeof(T));
}

template <typename T>
static inline Status alloc(T*& result, Size count, Size alignment = alignof(T)) {
	result = (T*)std::aligned_alloc(alignment, count * sizeof(T));
	return result != nullptr;
}

template <typename T>
static inline T* realloc(T* result, Size count) {
	return (T*)std::realloc(result, count * sizeof(T));
}

template <typename T>
static inline Status realloc(T*& result, Size count) {
	result = (T*)std::realloc(result, count * sizeof(T));
	return result != nullptr;
}

template <typename T>
static inline void free(T* ptr) {
	std::free((void*)ptr);
}

}

#endif
