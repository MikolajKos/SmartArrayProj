#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP

#include <memory>
#include <functional>
#include <unordered_map>

class CommandFactory {
	std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>> cmdMap_;
public:

};

#endif