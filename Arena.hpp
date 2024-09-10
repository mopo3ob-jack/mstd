#ifndef MSTD_ARENA_HPP
#define MSTD_ARENA_HPP

#include "memory.hpp"
#include <cstring>

#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <memoryapi.h>
#include <sysinfoapi.h>
#else
#error This library is not compatible with this system
#endif
#include <iostream>

namespace mstd {

class Arena {
public:
	Arena(Size maxSize = (1ull << (sizeof(Size) * 4)))
		: maxSize(maxSize) {

#ifdef __unix__
		first = (U8*)mmap(nullptr, maxSize, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		pageSize = sysconf(_SC_PAGESIZE);
#elif defined(_WIN32)
		first = (U8*)VirtualAlloc(nullptr, maxSize, MEM_RESERVE, PAGE_NOACCESS);
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		pageSize = sysInfo.dwPageSize;
#endif
		last = first;
		current = first;
	}

	~Arena() {
		if (first) {
#ifdef __unix__
			munmap(first, maxSize);
#elif defined(_WIN32)
			VirtualFree(first, maxSize, MEM_RELEASE);
#endif

			first = nullptr;
		}
	}

	template <typename T>
	T* reserve(Size count, const Size alignment = alignof(T)) {
		current += (Size)current % alignment;
		T* result = (T*)current;
		Size size = count * sizeof(T);
		current += size;

		if (current > last) {
			U8* newLast = current + pageSize - ((Size)current & (pageSize - 1));
#ifdef __unix__
			mprotect(last, newLast - last, PROT_READ | PROT_WRITE);
#elif defined(_WIN32)
			VirtualAlloc(last, newLast - last, MEM_COMMIT, PAGE_READWRITE);
#endif
			last = newLast;
		}

		return result;
	}

	template <typename T>
	T* append(Size count, T* data, const Size alignment = alignof(T)) {
		current += (Size)current % alignment;
		T* result = (T*)current;
		Size size = count * sizeof(T);
		current += size;

		if (current > last) {
			U8* newLast = current + pageSize - ((Size)current & (pageSize - 1));
#ifdef __unix__
			mprotect(last, newLast - last, PROT_READ | PROT_WRITE);
#elif defined(_WIN32)
			VirtualAlloc(last, newLast - last, MEM_COMMIT, PAGE_READWRITE);
#endif
			last = newLast;
		}

		memcpy(result, data, size);

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
