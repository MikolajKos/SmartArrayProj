#include <commands/HelpCommand.hpp>

int HelpCommand::execute(int argc, char* argv[]) {
	// Get help argument
	const char* cmd_name = argv[2];
	
	std::cout <<
		"Welcome to the SmartArray CLI Application.\n"
		"\n"
		"This command-line tool allows you to interact with and manage a dynamic array of elements.\n"
		"It supports various operations such as adding, removing, and printing elements,\n"
		"making it ideal for educational purposes, testing parsers, or experimenting with templated containers.\n"
		"\n"
		"You are currently viewing the help system.\n"
		"To learn more about a specific command, you can pass its name as an argument to the help command.\n"
		"\n"
		"Example:\n"
		"  help add\n"
		"\n"
		"This will display detailed usage information and available options for the 'add' command.\n";
	return 0;
}

int HelpCommand::expectedArgCount() {
	// return -1 if expected argument count is undedined
	return -1;
}