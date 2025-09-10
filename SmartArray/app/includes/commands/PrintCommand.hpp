#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>

/**
 * @brief Command to print all elements of a SmartArray.
 *
 * This template class implements the Command interface and provides
 * functionality to display all elements currently stored in the collection.
 *
 * @tparam T Type of elements stored in SmartArray
 */
template<typename T>
class PrintCommand : public Command {
	SmartArray<T>& array_; ///< Reference to the SmartArray to operate on
public:
	/**
	 * @brief Construct a new PrintCommand.
	 *
	 * @param ob Reference to the SmartArray to operate on
	 */
	PrintCommand(SmartArray<T>& ob) : array_(ob) {};

	/**
	 * @brief Execute the print command.
	 *
	 * Prints all elements in the SmartArray to standard output in the order
	 * they were added. If the collection is empty, an error handler may be invoked.
	 *
	 * @param argc Number of command-line arguments
	 * @param argv Array of command-line arguments
	 * @return int Result code (0 on success, non-zero on error)
	 */
	int execute(int argc, char* argv[]) override;

	/**
	 * @brief Get the expected number of arguments for this command.
	 *
	 * @return int Expected argument count (2 arguments expected)
	 */
	int expectedArgCount() override;

	/**
	 * @brief Get a textual description of the print command.
	 *
	 * Provides a brief description of the command's purpose and behavior.
	 *
	 * @return std::string Description of the command
	 */
	std::string description() override;
};

template<typename T>
int PrintCommand<T>::execute(int argc, char* argv[]) {
	return array_.printAll();
}

template<typename T>
int PrintCommand<T>::expectedArgCount() {
	return 2;
}

template<typename T>
std::string PrintCommand<T>::description() {
	return R"(Prints all elements currently stored in the collection.
Displays the elements in the order they were added.
No additional arguments are required for this command.)";
}

#endif