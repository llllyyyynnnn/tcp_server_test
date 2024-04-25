#include "functions.h"

unsigned int functions::client() {
	assign_variables(); // assign the important variables
	start("client"); // start up WSocket
	connect_client(); // connect to the socket using the variables assigned

	// start receiving & sending to the server, as we most likely have connected to it successfully by now if it has not exitted

	while (true) { 
		std::string str_input;
		std::getline(std::cin, str_input); // get the entire line, so we don't start sending multiple messages when adding spaces, etc

		int res = send(socket_main, str_input.c_str(), str_input.size() + 1, 0);	// Send data to the server that we are connected to.
		// str_input.c_str because the function uses a char, which we need to conver std::string to
		// it's also important that we add an extra byte to the size, as c requires an extra byte to close it (X chars + 1 extra)

		if (res == SOCKET_ERROR)
			error_exit("SOCKET_ERROR. The connection has either been invalidated or shut off.");
		else {
			ZeroMemory(buffer, 4096); // clear memory
			int received = recv(socket_main, buffer, 4096, 0); // data received and sent by server to client
			if (received > 0)
				std::cout << "Server -> " << std::string(buffer, 0, received) << std::endl;
		}
	}

	cleanup(); // clean before exitting
	return 0;
}