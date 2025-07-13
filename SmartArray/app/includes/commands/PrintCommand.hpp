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
};

template<typename T>
int PrintCommand<T>::execute(int argc, char* argv[]) {
	return array_.printAll();
}

template<typename T>
int PrintCommand<T>::expectedArgCount() {
	return 2;
}

#endif