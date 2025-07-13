#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command {
public:
	virtual int execute(int argc, char* argv[]) = 0;
	virtual int expectedArgCount() = 0;
	virtual ~Command() = default;
};

#endif