#ifndef MSTD_ARENA_HPP
#define MSTD_ARENA_HPP

#include "memory.hpp"
#include <cstring>

#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#endif

namespace mstd {

class Arena {
public:
	Arena(Size maxSize = (1ull << (sizeof(Size) / 2)))
		: maxSize(maxSize) {

#ifdef __unix__
		first = (U8*)mmap(nullptr, maxSize, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		pageSize = sysconf(_SC_PAGESIZE);
#endif
		last = first;
		current = first;
	}

	~Arena() {
		if (first) {
#ifdef __unix__
			munmap(first, maxSize);
#endif

			first = nullptr;
			current = nullptr;
		}
	}

	template <typename T>
	T* alloc(Size count, T* data = nullptr) {
		T* result = (T*)current;
		Size size = count * sizeof(T);
		current += size;

		if (current > last) {
			U8* newLast = current + pageSize - ((Size)current & (pageSize - 1));
#ifdef __unix__
			mprotect(last, newLast - last, PROT_READ | PROT_WRITE);
#endif
			last = newLast;
		}

		if (data) {
			memcpy(result, data, size);
		}

		return result;
	}

private:
	U8*           first;
	U8*           last;
	U8*           current;
	const Size    maxSize;
	Size          pageSize;
};

}

#endif
