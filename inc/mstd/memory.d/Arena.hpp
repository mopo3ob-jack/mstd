#ifndef MSTD_ARENA_HPP
#define MSTD_ARENA_HPP

#include "allocator.hpp"
#include <cstring>

#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <Windows.h>
#else
#error This library is not compatible with this system
#endif
#include <iostream>

namespace mstd {

class Arena {
public:
	Arena(Size maxSize) : maxSize(maxSize) {
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
			VirtualFree(first, 0, MEM_RELEASE);
#endif

			first = nullptr;
		}
	}

	Arena(Arena&) = delete;
	Arena& operator=(Arena&) = delete;

	Arena(Arena&& arena) = default;

	Arena& operator=(Arena&& arena) {
		this->~Arena();

		this->first = arena.first;
		this->pageSize = arena.pageSize;
		this->last = arena.last;
		this->current = arena.current;

		arena.first = nullptr;
		arena.last = nullptr;
		arena.current = nullptr;

		return *this;
	}

	template <typename T>
	T* reserve(Size count, Size alignment = alignof(T)) {
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
	T* append(Size count, const T* data, Size alignment = alignof(T)) {
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

	template <typename T>
	T* tell() const {
		return (T*)current;
	}

	void clear() {
		current = first;
	}

	template <typename T>
	void truncate(T* to) {
		current = (U8*)to;
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
