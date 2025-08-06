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

template <typename T, typename Parser>
class CommandHandler {
	SmartArray<T>& array_;
public:
	CommandHandler(SmartArray<T>& ob) : array_(ob) {};
	int handle(int argc, char* argv[]);
};

template <typename T, typename Parser>
int CommandHandler<T, Parser>::handle(int argc, char* argv[]) {
	Command* command = nullptr;
	
	if (argv[1] == NULL) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		return 2;
	}
	
	std::string cmd = argv[1];

	if (cmd == "pop")
		command = new PopCommand<T>(array_);
	else if (cmd == "print")
		command = new PrintCommand<T>(array_);
	else if (cmd == "add")
		command = new AddCommand<T, Parser>(array_);
	else if (cmd == "help")
		command = new HelpCommand();
	else
	{
		CommandErrorHandler::cmd_handler(CommandErrorHandler::CMD_NOT_FOUND);
		return 2;
	}

	int expectedArgs = command->expectedArgCount();
	if (expectedArgs != argc && expectedArgs != -1) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		delete command;
		return 2;
	}

	int result = command->execute(argc, argv);
	delete command;
	return result;
}

#endif