#ifndef MSTD_TCPSERVER_HPP
#define MSTD_TCPSERVER_HPP

#include "Socket.hpp"
#include "../misc.d/primitive.h"
#include <iostream>
#include <vector>

namespace mstd {

class TCPServer : public Socket {
public:
	Status open(U32 backlogSize, U16 port, U32 address = INADDR_ANY) {
		handle = socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in sockAddress = {
			.sin_family = AF_INET,
			.sin_port = port,
			.sin_addr = {
				.s_addr = htonl(address)
			}
		};

		if (bind(handle, (sockaddr*)&sockAddress, sizeof(sockAddress))) {
			return 1;
		}

		if (listen(handle, backlogSize)) {
			return 1;
		}

		return 0;
	}

	Socket accept() {
		sockaddr_in client;
		Size clientSize = sizeof(client);
		Handle clientHandle = ::accept(handle, (sockaddr*)&client, (socklen_t*)&clientSize);
		if (clientHandle == -1) {
			return Socket(-1);
		}

		return Socket(clientHandle);
	}
};

}

#endif
