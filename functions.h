#pragma once

#include<iostream>
#include<string>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace functions {
	inline char buffer[4096];

	unsigned int client();
	unsigned int server();

	inline std::string connection_address;
	inline int connection_port = 1000;

	inline SOCKET socket_main;
	inline SOCKET socket_client;
	inline sockaddr_in sin_;
	inline sockaddr_in sin_client;

	inline WSAData WSData;
	inline WORD WSock_version = MAKEWORD(2, 2);

	void assign_variables();
	void start(std::string version);
	void connect_client();
	void server_listen();
	void cleanup();
	void error_exit(std::string reason);
}