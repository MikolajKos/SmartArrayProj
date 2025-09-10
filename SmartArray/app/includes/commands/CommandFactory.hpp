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
#include <commands/ClearCommand.hpp>
#include <SmartArray.hpp>

/**
 * @brief Factory class to create command objects.
 *
 * This template class maps command names to their corresponding Command objects
 * and provides a method to create commands dynamically based on a string identifier.
 *
 * @tparam T Type of elements stored in SmartArray
 * @tparam Parser Parser type used to parse input arguments into objects of type T
 */
template<typename T, typename Parser>
class CommandFactory {
	std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>> cmdMap_; ///< Map of command names to factory functions
	SmartArray<T>& array_; ///< Reference to the SmartArray used by commands
public:
	/**
	 * @brief Construct a new CommandFactory.
	 *
	 * Initializes the mapping of command names to the corresponding command objects.
	 *
	 * @param ob Reference to the SmartArray used by created commands
	 */
	CommandFactory(SmartArray<T>& ob) : array_(ob) {
		cmdMap_["add"] = [this]() {return std::make_unique<AddCommand<T, Parser>>(array_);};
		cmdMap_["help"] = [this]() {return std::make_unique<HelpCommand<T, Parser>>(array_);};
		cmdMap_["pop"] = [this]() {return std::make_unique<PopCommand<T>>(array_);};
		cmdMap_["print"] = [this]() {return std::make_unique<PrintCommand<T>>(array_);};
		cmdMap_["clear"] = [this]() {return std::make_unique<ClearCommand<T>>(array_);};
	};

	/**
	 * @brief Create a command object based on the command name.
	 *
	 * Looks up the command name in the internal map and returns a unique_ptr
	 * to the corresponding Command object. Returns nullptr if the command
	 * is not found.
	 *
	 * @param name Name of the command to create
	 * @return std::unique_ptr<Command> Pointer to the created Command object, or nullptr if not found
	 */
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