#include <iostream>
#include <handlers/CommandErrorHandler.hpp>

char* CommandErrorHandler::messages[] = {
	"W Wrong argument list given"
};

void CommandErrorHandler::cmd_handler(enum Errors error, const char* info) {
	std::cout << messages[error] + 2 << std::endl;

	if (info != nullptr && info[0] != '\0') {
		std::cerr << info << std::endl;
	}

	if (messages[error][0] == 'E') {
		system("pause");
		exit(1);
	}
}