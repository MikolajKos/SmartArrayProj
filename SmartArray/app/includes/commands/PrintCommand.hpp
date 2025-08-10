#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>

template<typename T>
class PrintCommand : public Command {
	SmartArray<T>& array_;
public:
	PrintCommand(SmartArray<T>& ob) : array_(ob) {};

	int execute(int argc, char* argv[]) override;
	int expectedArgCount() override;
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