#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include <handlers/CommandErrorHandler.hpp>
#include <commands/CommandHandler.hpp>
#include <commands/PopCommand.hpp>
#include <commands/PrintCommand.hpp>
#include <commands/AddCommand.hpp>
#include <commands/HelpCommand.hpp>
#include <SmartArray.hpp>
#include <commands/CommandFactory.hpp>
#include <IParser.hpp>

/**
 * @brief Handles commands for a SmartArray using a specified parser.
 *
 * This template class is responsible for processing command-line arguments,
 * creating the appropriate command via CommandFactory, and executing it.
 *
 * @tparam T Type of elements stored in SmartArray
 */
template <typename T>
class CommandHandler {
	SmartArray<T>& array_;	///< Reference to the SmartArray being manipulated
	IParser<T>& parser_; ///< Reference to the data type parser
public:
	/**
	* @brief Construct a new CommandHandler.
	*
	* @param ob Reference to the SmartArray object to manage
	*/
	CommandHandler(SmartArray<T>& ob, IParser<T>& parser) : array_(ob), parser_(parser) {};

	/**
	* @brief Handle command-line arguments and execute the corresponding command.
	*
	* This function checks for argument validity, uses CommandFactory to create
	* the command object, verifies the expected number of arguments, and executes it.
	*
	* @param argc Number of command-line arguments
	* @param argv Array of command-line arguments
	* @return int Execution result code (0 on success, non-zero on error)
	*/
	int handle(int argc, char* argv[]);
};

template <typename T>
int CommandHandler<T>::handle(int argc, char* argv[]) {
	if (argv[1] == NULL) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		return 2;
	}
	
	CommandFactory<T> factory(array_, parser_);
	// Pass command name as a parameter
	std::unique_ptr<Command> command = factory.createCommand(argv[1]);
	if (!command) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::CMD_NOT_FOUND);
		return 2;
	}
	
	int expectedArgs = command->expectedArgCount();
	if (expectedArgs != argc && expectedArgs != -1) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		return 2;
	}

	int result = command->execute(argc, argv);
	return result;
}

#endif