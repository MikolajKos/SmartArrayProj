#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

/**
 * @brief Abstract base class for all commands.
 *
 * Defines the interface for commands that can be executed by CommandHandler.
 * All concrete command classes should inherit from this class and implement
 * the pure virtual methods.
 */
class Command {
public:
	/**
	 * @brief Execute the command.
	 *
	 * This is a pure virtual method that must be implemented by derived classes.
	 * It performs the command's main action.
	 *
	 * @param argc Number of command-line arguments
	 * @param argv Array of command-line arguments
	 * @return int Result code (0 on success, non-zero on error)
	 */
	virtual int execute(int argc, char* argv[]) = 0;

	/**
	 * @brief Get the expected number of arguments for this command.
	 *
	 * This is a pure virtual method that must be implemented by derived classes.
	 * It returns the number of arguments the command expects.
	 * A return value of -1 indicates that the command can accept an arbitrary
	 * number of arguments.
	 *
	 * @return int Expected argument count, or -1 if the number of arguments is not fixed
	 */
	virtual int expectedArgCount() = 0;

	/**
	 * @brief Get a textual description of the command.
	 *
	 * Can be overridden by derived classes to provide detailed instructions
	 * for using the command. Default implementation returns a placeholder string.
	 *
	 * @return std::string Command description
	 */
	virtual std::string description() {
		return "No description available";
	}

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Command() = default;
};

#endif