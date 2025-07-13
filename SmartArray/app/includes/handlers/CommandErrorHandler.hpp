#ifndef COMMAND_ERROR_HANDLER_HPP
#define COMMAND_ERROR_HANDLER_HPP

class CommandErrorHandler {
	static const char* messages[];
public:
	enum Errors {
		ARGS_EXCEPTION,
		CMD_NOT_FOUND,
		TOT_ERROR // Total number of errors 
	};

	static void cmd_handler(enum Errors error, const char* info = "");
};

#endif