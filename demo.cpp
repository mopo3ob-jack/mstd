#include "Arena.hpp"
#include <iostream>
#include <time.h>

int main(int argc, char** argv) {
	using namespace mstd;

	Arena arena;
	clock_t start = clock();
	std::cout << arena.alloc<U64>(256) << std::endl;
	clock_t end = clock();

	U64 firstTime = end - start;

	start = clock();
	std::cout << arena.alloc<U64>(256) << std::endl;
	end = clock();

	U64 secondTime = end - start;

	start = clock();
	U64* asdf = arena.alloc<U64>(256);
	end = clock();

	U64 thirdTime = end - start;

	std::cout << firstTime << "\n" << secondTime << "\n" << thirdTime << "\n";

	return 0;
}
