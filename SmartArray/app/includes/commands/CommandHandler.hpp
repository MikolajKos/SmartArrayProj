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

template <typename T, typename Parser>
class CommandHandler {
	SmartArray<T>& array_;
public:
	CommandHandler(SmartArray<T>& ob) : array_(ob) {};
	int handle(int argc, char* argv[]);
};

template <typename T, typename Parser>
int CommandHandler<T, Parser>::handle(int argc, char* argv[]) {
	if (argv[1] == NULL) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		return 2;
	}
	
	CommandFactory<T, Parser> factory(array_);
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