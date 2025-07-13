#ifndef POP_COMMAND_HPP
#define POP_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>

template <typename T>
class PopCommand : public Command {
	SmartArray<T>& array_;
public:
	PopCommand(SmartArray<T>& ob) : array_(ob) {};

	int PopCommand::execute(int argc, char* argv[]) override;
	int PopCommand::expectedArgCount() override;
};

template <typename T>
int PopCommand<T>::execute(int argc, char* argv[]) {

	return 0;
}

template <typename T>
int PopCommand<T>::expectedArgCount() {
	return 2;
}

#endif