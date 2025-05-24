#ifndef MSTD_SOCKET_HPP
#define MSTD_SOCKET_HPP

#ifdef __unix__
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#elif defined(_WIN32)
#include <winsock2.h>
#else
#error This library is not compatible with this system
#endif

#include "../misc.d/primitive.h"

namespace mstd {

class Socket {
public:
#ifdef __unix__
	using Handle = int;
#elif defined(_WIN32)
	using Handle = SOCKET;
#endif

	Socket() {
		handle = -1;
	}

	Socket(Handle handle) {
		this->handle = handle;
	}

	~Socket() {
		if (handle != -1) {
#ifdef __unix__
			close(handle);
#elif defined(_WIN32)
			closesocket(handle);
#endif
			handle = -1;
		}
	}

	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;

	Socket(Socket&& socket) {
		this->~Socket();
		this->handle = socket.handle;
		socket.handle = -1;
	}

	Socket& operator=(Socket&& socket) {
		this->~Socket();
		this->handle = socket.handle;
		socket.handle = -1;
		return *this;
	}

	operator Bool() const {
		return handle == -1;
	}

protected:
	Handle handle;
};

}

#endif
