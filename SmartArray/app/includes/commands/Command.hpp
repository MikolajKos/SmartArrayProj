#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class Command {
public:
	virtual int execute(int argc, char* argv[]) = 0;
	virtual int expectedArgCount() = 0;
	virtual std::string description() {
		return "No description available";
	}

	virtual ~Command() = default;
};

#endif