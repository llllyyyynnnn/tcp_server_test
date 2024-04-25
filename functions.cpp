#include "functions.h"

namespace functions {
	void assign_variables() {
		std::cout << "Enter the IP address to connect to. Enter 0 to use localhost." << std::endl;
		std::cin >> connection_address;

		if (connection_address == "0")
			connection_address = "127.0.0.1";

		std::cout << "Enter a port." << std::endl;
		std::cin >> connection_port;
		std::cout << "Assigned connection to " << connection_address << ":" << connection_port << std::endl;
	} // simple variable assigning

	void start(std::string version) { // start sockets, etc
		int res = WSAStartup(WSock_version, &WSData); // the most important part as it defines the winsocket version and other important variables
		if (res != 0) // anything other than 0 is not successful, exit and return the error code
			error_exit(std::to_string(res));

		socket_main = socket(AF_INET, SOCK_STREAM, 0); // main socket, used both for client & server
		if (socket_main == INVALID_SOCKET) // check for invalid return values
			error_exit("INVALID_SOCKET");

		sin_.sin_family = AF_INET; // assign variables, mostly default
		sin_.sin_port = htons(connection_port);
		if (version == "client") // client and server use different methods, had to do this (there's definetly more efficient methods though)
			inet_pton(AF_INET, connection_address.c_str(), &sin_.sin_addr);
		else if (version == "server")
			sin_.sin_addr.S_un.S_addr = INADDR_ANY;

		std::cout << "Successfully prepared socket" << std::endl;
	}

	void connect_client() {
		int res = connect(socket_main, (sockaddr*)&sin_, sizeof(sin_)); // connect using the given information
		if (res == SOCKET_ERROR)
			error_exit("SOCKET_ERROR");
	}

	void server_listen() {
		bind(socket_main, (sockaddr*)&sin_, sizeof(sin_));
		listen(socket_main, SOMAXCONN); // bind and start listening

		int sin_client_size = sizeof(sin_client);
		socket_client = accept(socket_main, (sockaddr*)&sin_client, &sin_client_size);

		char hostname[NI_MAXHOST];
		char connected_port[NI_MAXSERV];

		ZeroMemory(hostname, NI_MAXHOST);
		ZeroMemory(connected_port, NI_MAXSERV); // clear memory

		if (getnameinfo((sockaddr*)&sin_client, sizeof(sin_client), hostname, NI_MAXHOST, connected_port, NI_MAXSERV, 0) == 0)
			std::cout << hostname << ":" << connected_port << std::endl;
		else {
			inet_ntop(AF_INET, &sin_client.sin_addr, hostname, NI_MAXHOST);
			std::cout << hostname << ":" << connected_port << ntohs(sin_client.sin_port) << std::endl;
		} // get client information

		closesocket(socket_main); // close the main socket, we're now using socket_client
	}

	void cleanup() {
		closesocket(socket_main); // incase the socket was opened, close it.
		WSACleanup(); // clean up WSA
	}

	void error_exit(std::string reason) {
		std::cout << "Failed (" << reason << ")" << std::endl;
		cleanup(); // it's important to clean up before exitting
		exit(1); // exit with code 1
	}
}