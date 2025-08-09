#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP

#include <memory>
#include <functional>
#include <unordered_map>
#include <commands/Command.hpp>
#include <commands/AddCommand.hpp>
#include <commands/HelpCommand.hpp>
#include <commands/PopCommand.hpp>
#include <commands/PrintCommand.hpp>
#include <SmartArray.hpp>

template<typename T, typename Parser>
class CommandFactory {
	std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>> cmdMap_;
	SmartArray<T>& array_;
public:
	CommandFactory(SmartArray<T>& ob) : array_(ob) {
		cmdMap_["add"] = [this]() {return std::make_unique<AddCommand<T, Parser>>(array_);};
		cmdMap_["help"] = []() {return std::make_unique<HelpCommand>();};
		cmdMap_["pop"] = [this]() {return std::make_unique<PopCommand<T>>(array_);};
		cmdMap_["print"] = [this]() {return std::make_unique<PrintCommand<T>>(array_);};
	};

	std::unique_ptr<Command> createCommand(std::string name);
};

// Implementation
template<typename T, typename Parser>
std::unique_ptr<Command> CommandFactory<T, Parser>::createCommand(std::string name) {
	auto it = cmdMap_.find(name);
	if (it != cmdMap_.end()) {
		return (it->second)();
	}
	return nullptr;
}

#endif