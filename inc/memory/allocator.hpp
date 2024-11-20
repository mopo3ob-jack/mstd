#ifndef MSTD_MEMORY_HPP
#define MSTD_MEMORY_HPP

#include "../misc/primitive.h"

#include <cstdlib>

namespace mstd {

#ifdef MSTD_COUNT_ALLOCATIONS
extern Size allocationCount;
#endif

template <typename T>
static inline T* alloc(Size count, Size alignment = alignof(T)) {
#ifdef MSTD_COUNT_ALLOCATIONS
	++allocationCount;
#endif
	return (T*)std::aligned_alloc(alignment, count * sizeof(T));
}

template <typename T>
static inline Status alloc(T*& result, Size count, Size alignment = alignof(T)) {
#ifdef MSTD_COUNT_ALLOCATIONS
	++allocationCount;
#endif
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
#ifdef MSTD_COUNT_ALLOCATIONS
	--allocationCount;
#endif
	std::free((void*)ptr);
}

}

#endif
