#ifndef MSTD_MEMORY_HPP
#define MSTD_MEMORY_HPP

#include "../misc.d/primitive.h"

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
#ifdef _WIN32
	return (T*)_aligned_malloc(count * sizeof(T), alignment);
#else
	return (T*)std::aligned_alloc(alignment, count * sizeof(T));
#endif
}

template <typename T>
static inline Status alloc(T*& result, Size count, Size alignment = alignof(T)) {
#ifdef MSTD_COUNT_ALLOCATIONS
	++allocationCount;
#endif
#ifdef _WIN32
	result = (T*)_aligned_malloc(count * sizeof(T), alignment);
#else
	result = (T*)std::aligned_alloc(alignment, count * sizeof(T));
#endif
	return result != nullptr;
}

template <typename T>
static inline Status realloc(T*& ptr, Size count, Size alignment = alignof(T)) {
#ifdef _WIN32
	ptr = _aligned_realloc((void*)ptr, count, alignment);
#else
	// TODO
	// Add reallocation alignment for unix
	ptr = (T*)std::realloc(ptr, count * sizeof(T));
#endif
	return ptr != nullptr;
}

template <typename T>
static inline void free(T* ptr) {
#ifdef MSTD_COUNT_ALLOCATIONS
	--allocationCount;
#endif
#ifdef _WIN32
	_aligned_free((void*)ptr);
#else
	std::free((void*)ptr);
#endif
}

}

#endif
