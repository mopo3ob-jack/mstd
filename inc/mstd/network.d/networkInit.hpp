#ifndef MSTD_NETWORKINIT_HPP
#define MSTD_NETWORKINIT_HPP

#ifdef __unix__
#elif defined(_WIN32)
#include <winsock2.h>
#else
#error This library is not compatible with this system
#endif

#include "../misc.d/primitive.h"
#include "../misc.d/errorText.h"
#include <iostream>

namespace mstd {

#ifdef __unix__
constexpr Status initNetwork() {
	return 0;
}
#elif defined(_WIN32)
Status networkInit() {
	WSADATA wsaData;
	Status result;
	if (result = (Status)WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		std::cerr << errorText << "Could not initialize windows networking" << std::endl;
	}

	return result;
}
#endif

}

#endif
