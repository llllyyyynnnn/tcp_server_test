#include "functions.h"

int main() {
	std::cout << "Enter 1 for client and 2 for server." << std::endl;
	int choice = 0;
	std::cin >> choice;

	switch (choice) {
	case 1:
		functions::client();
		break;
	case 2:
		functions::server();
		break;
	}
}