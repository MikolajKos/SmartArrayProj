#ifndef CLEAR_COMMAND_HPP
#define CLEAR_COMMAND_HPP

#include <commands/Command.hpp>
#include <SmartArray.hpp>
#include <iostream>

template <typename T>
class ClearCommand : public Command {
	SmartArray<T>& array_;
public:
	ClearCommand(SmartArray<T>& ob) : array_(ob) {};

	int execute(int argc, char* argv[]) override {
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

	int expectedArgCount() override {
		return 2;
	}
};

#endif