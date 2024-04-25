#include "functions.h"

unsigned int functions::server() {
	assign_variables();
	start("server");
	server_listen();

	while (true) {
		ZeroMemory(buffer, 4096); // clear buffer
		int received = recv(socket_client, buffer, 4096, 0); // get data from socket_client, which is connected to the client
		if (received == SOCKET_ERROR)
			error_exit("SOCKET_ERROR"); // if invalid, exit

		if (received == 0)
			error_exit("Received 0 bytes."); // if nothing has been received, exit as the client has most likely closed or lost connection

		std::cout << "Client -> " << std::string(buffer, 0, received) << std::endl; // print out received data in the form of a string

		std::string message;
		std::getline(std::cin, message); // send to the client

		send(socket_client, (char*)&message[0], sizeof(message) + 1, 0); // send 
	}

	cleanup();
}
