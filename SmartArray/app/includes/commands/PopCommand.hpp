#ifndef POP_COMMAND_HPP
#define POP_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <iostream>

template <typename T>
class PopCommand : public Command {
	SmartArray<T>& array_;
public:
	PopCommand(SmartArray<T>& ob) : array_(ob) {};

	int execute(int argc, char* argv[]) override;
	int expectedArgCount() override;
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