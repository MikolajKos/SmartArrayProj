#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include <handlers/CommandErrorHandler.hpp>
#include <commands/CommandHandler.hpp>
#include <commands/PopCommand.hpp>
#include <commands/PrintCommand.hpp>
#include <commands/AddCommand.hpp>
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
	
	if (argv[1] == NULL)
		return 1;
	
	std::string cmd = argv[1];

	if (cmd == "pop")
		command = new PopCommand<T>(array_);
	else if (cmd == "print")
		command = new PrintCommand<T>(array_);
	else if (cmd == "add")
		command = new AddCommand<T, Parser>(array_);
	else
	{
		CommandErrorHandler::cmd_handler(CommandErrorHandler::CMD_NOT_FOUND);
		return 1;
	}

	if (command->expectedArgCount() != argc) {
		CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
		delete command;
		return 1;
	}

	int result = command->execute(argc, argv);
	delete command;
	return result;
}

#endif