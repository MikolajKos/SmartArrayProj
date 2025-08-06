#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include <commands/Command.hpp>
#include <iostream>

class HelpCommand : public Command {
public:
	HelpCommand() {};

	int execute(int argc, char* argv[]) override;
	int expectedArgCount() override;
};

// Implementatiom in cpp

#endif