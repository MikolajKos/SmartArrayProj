#ifndef CLEAR_COMMAND_HPP
#define CLEAR_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <iostream>

/**
 * @brief Command to clear all elements from a SmartArray.
 *
 * This template class implements the Command interface and allows clearing
 * all elements from a SmartArray after user confirmation.
 *
 * @tparam T Type of elements stored in SmartArray
 */
template <typename T>
class ClearCommand : public Command {
	SmartArray<T>& array_;	///< Reference to the SmartArray to clear
public:
	/**
	* @brief Construct a new ClearCommand.
	*
	* @param ob Reference to the SmartArray to operate on
	*/
	ClearCommand(SmartArray<T>& ob) : array_(ob) {};

	/**
	* @brief Execute the clear command.
	*
	* Asks the user for confirmation before clearing all elements.
	* If the user confirms, all elements in the SmartArray are removed.
	*
	* @param argc Number of command-line arguments
	* @param argv Array of command-line arguments
	* @return int Result code (0 on success, non-zero on error)
	*/
	int execute(int argc, char* argv[]) override;

	/**
	* @brief Get the expected number of arguments for this command.
	*
	* @return int Expected argument count (always 2 for this command)
	*/
	int expectedArgCount() override;

	/**
	* @brief Get a textual description of the clear command.
	*
	* Provides instructions for using the command and notes that no additional
	* arguments are required.
	*
	* @return std::string Description of the command
	*/
	std::string description() override;
};

template<typename T>
int ClearCommand<T>::execute(int argc, char* argv[]) {
	std::string choice;

	do {
		std::cout << "Are you sure you want to delete all records? (y/n)" << "\n";
		std::cin >> choice;

		if (choice.at(0) == 'n')
			return 0;
	} while (choice.at(0) != 'y');

	unsigned size = array_.size();
	array_.clear();

	std::cout << "Successfully deleted " << size << " records" << "\n";

	return 0;
}

template<typename T>
int ClearCommand<T>::expectedArgCount() {
	return 2;
}

template<typename T>
std::string ClearCommand<T>::description() {
	return R"(Clears all elements from the collection.
After this command, the collection will be empty.
No additional arguments are required.)";
}

#endif