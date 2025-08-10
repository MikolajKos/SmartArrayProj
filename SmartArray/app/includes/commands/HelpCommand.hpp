#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include <commands/Command.hpp>
#include <commands/CommandFactory.hpp>
#include <iostream>
#include <memory>
#include <functional>
#include <SmartArray.hpp>

template <typename T, typename Parser>
class HelpCommand : public Command {
	SmartArray<T>& array_;
public:
	HelpCommand(SmartArray<T>& ob): array_(ob) {};

	int execute(int argc, char* argv[]) override;
	int expectedArgCount() override;
	std::string description() override;
};

template <typename T, typename Parser>
int HelpCommand<T, Parser>::execute(int argc, char* argv[]) {
	// Gets help argument
	const char* cmd_name = argv[2];

	// Execute when no command arguments were passed
	if (argc < 3) {
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

	// Command argument was given
	CommandFactory<T, Parser> factory(array_);

	std::unique_ptr<Command> command = factory.createCommand(cmd_name);
	if (!command) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::CMD_NOT_FOUND);
		return 2;
	}

	std::cout << command->description();

	return 0;
}

template <typename T, typename Parser>
int HelpCommand<T, Parser>::expectedArgCount() {
	// return -1 if expected argument count is undedined
	return -1;
}

template <typename T, typename Parser>
std::string HelpCommand<T, Parser>::description() {
	return "I see you ask for a lot of help ;)\n";
}

#endif