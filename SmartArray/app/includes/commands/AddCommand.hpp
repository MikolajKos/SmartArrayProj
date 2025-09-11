#ifndef ADD_COMMAND_HPP
#define ADD_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <IParser.hpp>
#include <iostream>

/**
 * @brief Command to add a new element to a SmartArray.
 *
 * This template class implements the Command interface and allows adding
 * elements to a SmartArray using a specified parser for input arguments.
 *
 * @tparam T Type of elements stored in SmartArray
 * @tparam Parser Parser type used to parse command-line arguments into objects of type T
 */
template<typename T>
class AddCommand : public Command {
	SmartArray<T>& array_;	///< Reference to the SmartArray to add elements to
	IParser<T>& parser_; ///< Reference to the T type parser for specific to data type operations
public:
	/**
	* @brief Construct a new AddCommand.
	*
	* @param ob Reference to the SmartArray to operate on
	* @param parser Reference to the data type parser
	*/
	AddCommand(SmartArray<T>& ob, IParser<T>& parser) : array_(ob), parser_(parser) {};

	/**
	* @brief Execute the add command.
	*
	* Parses the input arguments using the Parser and adds the resulting object
	* to the SmartArray.
	*
	* @param argc Number of command-line arguments
	* @param argv Array of command-line arguments
	* @return int Result code (0 on success, non-zero on error)
	*/
	int execute(int argc, char* argv[]) override;

	/**
	* @brief Get the expected number of arguments for this command.
	*
	* @return int Expected argument count
	*/
	int expectedArgCount() override;

	/**
	* @brief Get a textual description of the add command.
	*
	* Provides instructions for using the command and the expected argument format.
	*
	* @return std::string Description of the command
	*/
	std::string description() override;
};

template<typename T>
int AddCommand<T>::execute(int argc, char* argv[]) {
	T obj = parser_.parseData(argv);
	return array_.push(obj);
}

template<typename T>
int AddCommand<T>::expectedArgCount() {
	return parser_.getArgCount();
}

template<typename T>
std::string AddCommand<T>::description() {
	    return std::string(R"(Adds a new element to the collection.
The command requires a specific set of arguments depending on the element type.
Use the appropriate format and provide all necessary fields.
For multi-word arguments, enclose them in double quotes ("").)") + "\n\nType info:\n" + parser_.description() + "\n";
}

#endif