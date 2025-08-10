#ifndef ADD_COMMAND_HPP
#define ADD_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <iostream>

template<typename T, typename Parser>
class AddCommand : public Command {
	SmartArray<T>& array_;
public:
	AddCommand(SmartArray<T>& ob) : array_(ob) {};

	int execute(int argc, char* argv[]) override;
	int expectedArgCount() override;
	std::string description() override;
};

template<typename T, typename Parser>
int AddCommand<T, Parser>::execute(int argc, char* argv[]) {
	T obj = Parser::parseData(argv);
	return array_.push(obj);
}

template<typename T, typename Parser>
int AddCommand<T, Parser>::expectedArgCount() {
	return Parser::getArgCount();
}

template<typename T, typename Parser>
std::string AddCommand<T, Parser>::description() {
	    return std::string(R"(Adds a new element to the collection.
The command requires a specific set of arguments depending on the element type.
Use the appropriate format and provide all necessary fields.
For multi-word arguments, enclose them in double quotes ("").)") + "\n\nType info:\n" + Parser::description() + "\n";
}

#endif