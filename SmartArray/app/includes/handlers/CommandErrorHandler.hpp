#ifndef COMMAND_ERROR_HANDLER_HPP
#define COMMAND_ERROR_HANDLER_HPP

/**
 * @brief Handles errors related to command execution in the SmartArray CLI.
 *
 * This class provides static methods and predefined error messages to handle
 * situations such as incorrect arguments or unknown commands.
 */
class CommandErrorHandler {
	static const char* messages[]; ///< Array of predefined error messages
public:
	/**
	 * @brief Enumeration of possible command errors.
	 */
	enum Errors {
		ARGS_EXCEPTION, ///< Thrown when the number of arguments is incorrect
		CMD_NOT_FOUND,  ///< Thrown when the specified command does not exist
		TOT_ERROR       ///< Total number of errors defined
	};

	/**
	 * @brief Handle a command-related error.
	 *
	 * Prints or logs the appropriate error message based on the error type.
	 * An optional info string can provide additional context.
	 *
	 * @param error The type of error (from Errors enum)
	 * @param info Optional additional information about the error
	 */
	static void cmd_handler(enum Errors error, const char* info = "");
};

#endif