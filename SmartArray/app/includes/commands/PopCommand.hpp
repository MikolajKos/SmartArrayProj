#ifndef POP_COMMAND_HPP
#define POP_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <iostream>

/**
 * @brief Command to remove the last element from a SmartArray.
 *
 * This template class implements the Command interface and provides
 * functionality to pop the last element from the collection.
 *
 * @tparam T Type of elements stored in SmartArray
 */
template <typename T>
class PopCommand : public Command {
	SmartArray<T>& array_; ///< Reference to the SmartArray to operate on
public:
	/**
	 * @brief Construct a new PopCommand.
	 *
	 * @param ob Reference to the SmartArray to operate on
	 */
	PopCommand(SmartArray<T>& ob) : array_(ob) {};

	/**
	 * @brief Execute the pop command.
	 *
	 * Removes the last element from the SmartArray and prints it to standard output.
	 * If the collection is empty, no action is performed.
	 *
	 * @param argc Number of command-line arguments
	 * @param argv Array of command-line arguments
	 * @return int Result code (0 on success)
	 */
	int execute(int argc, char* argv[]) override;

	/**
	 * @brief Get the expected number of arguments for this command.
	 *
	 * @return int Expected argument count
	 */
	int expectedArgCount() override;

	/**
	 * @brief Get a textual description of the pop command.
	 *
	 * Provides a brief description of the command's purpose and behavior.
	 *
	 * @return std::string Description of the command
	 */
	std::string description() override;
};

template <typename T>
int PopCommand<T>::execute(int argc, char* argv[]) {
	std::cout << array_.pop() << std::endl;
	return 0;
}

template <typename T>
int PopCommand<T>::expectedArgCount() {
	return 2;
}

template <typename T>
std::string PopCommand<T>::description() {
	return R"(Removes the last element from the collection.
If the collection is empty, no action is performed.
No additional arguments are required for this command.)";
}

#endif