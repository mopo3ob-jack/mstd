#ifndef MSTD_PREFETCH_HPP
#define MSTD_PREFETCH_HPP

#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <memoryapi.h>
#include <sysinfoapi.h>
#else
#error This library is not compatible with this system
#endif
#include "allocator.hpp"

namespace mstd {

template <typename T>
static Status prefetch(T* address, Size length) {
#ifdef __unix__
	const Size pageSize = sysconf(_SC_PAGESIZE);
	void* page = (void*)((Size)address & ~(pageSize - 1));
	length += address - page;
	return madvise(page, length, MADV_WILLNEED);
#elif defined(_WIN32)
#endif
}

}

#endif
