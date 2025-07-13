#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include <handlers/CommandErrorHandler.hpp>
#include <commands/CommandHandler.hpp>
#include <commands/PopCommand.hpp>
#include <commands/PrintCommand.hpp>
#include <SmartArray.hpp>

template <typename T>
class CommandHandler {
	SmartArray<T>& array_;
public:
	CommandHandler(SmartArray<T>& ob) : array_(ob) {};
	int handle(int argc, char* argv[]);
};

template <typename T>
int CommandHandler<T>::handle(int argc, char* argv[]) {
	Command* command = nullptr;
	
	if (argv[1] == NULL)
		return 1;
	
	std::string cmd = argv[1];

	if (cmd == "pop") {
		command = new PopCommand<T>(array_);
		if (command->expectedArgCount() != argc) {
			CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
			delete command;
			return 1;
		}
	}
	else if (cmd == "print") {
		command = new PrintCommand<T>(array_);
		if (command->expectedArgCount() != argc) {
			CommandErrorHandler::cmd_handler(CommandErrorHandler::ARGS_EXCEPTION);
			delete command;
			return 1;
		}
	}
	else
	{
		CommandErrorHandler::cmd_handler(CommandErrorHandler::CMD_NOT_FOUND);
		return 1;
	}

	int result = command->execute(argc, argv);
	delete command;
	return result;
}

#endif