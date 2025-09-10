#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include <commands/Command.hpp>
#include <commands/CommandFactory.hpp>
#include <iostream>
#include <memory>
#include <functional>
#include <SmartArray.hpp>

/**
 * @brief Command to display help information for SmartArray CLI commands.
 *
 * This template class implements the Command interface and provides detailed
 * usage instructions for all commands, or for a specific command if a name
 * is passed as an argument.
 *
 * @tparam T Type of elements stored in SmartArray
 * @tparam Parser Parser type used to provide description of the element type T
 */
template <typename T, typename Parser>
class HelpCommand : public Command {
	SmartArray<T>& array_; ///< Reference to the SmartArray used by commands
public:
	/**
	 * @brief Construct a new HelpCommand.
	 *
	 * @param ob Reference to the SmartArray to operate on
	 */
	HelpCommand(SmartArray<T>& ob): array_(ob) {};

	/**
	 * @brief Execute the help command.
	 *
	 * If no command name is provided, displays general help information for
	 * the SmartArray CLI application. If a command name is given, displays
	 * the description for that specific command.
	 *
	 * @param argc Number of command-line arguments
	 * @param argv Array of command-line arguments
	 * @return int Result code (0 on success, non-zero on error)
	 */
	int execute(int argc, char* argv[]) override;

	/**
	 * @brief Get the expected number of arguments for the help command.
	 *
	 * A return value of -1 indicates that the command can accept an arbitrary
	 * number of arguments.
	 *
	 * @return int Expected argument count (-1 for undefined)
	 */
	int expectedArgCount() override;

	/**
	 * @brief Get a textual description of the help command.
	 *
	 * Provides a brief message about the purpose of the help command.
	 *
	 * @return std::string Description of the command
	 */
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