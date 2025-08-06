#include <commands/HelpCommand.hpp>

int HelpCommand::execute(int argc, char* argv[]) {
	std::cout << "Teststst" << std::endl;
	return 0;
}

int HelpCommand::expectedArgCount() {
	// return -1 if expected argument count is undedined
	return -1;
}