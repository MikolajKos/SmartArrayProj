#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <string>

/**
 * @brief Abstract interface for parsing objects from command-line arguments.
 *
 * This template class defines a contract for parsing objects of type T
 * from an array of C-style strings, validating the parsed data,
 * and providing metadata about expected arguments.
 *
 * Implementations of this interface are responsible for:
 * - Converting command-line arguments to objects of type T.
 * - Specifying the expected number of arguments.
 * - Providing a human-readable description of the arguments.
 * - Performing any necessary validation of input data.
 *
 * @tparam T The type of object that will be parsed.
 *
 * @note This interface is intended to decouple parsing logic from command
 *       execution, allowing commands to remain generic and type-agnostic.
 */
template <typename T>
class IParser {
public:
    /**
	 * @brief Parse an object of type T from command-line arguments.
	 *
	 * Implementations should read the arguments in the expected order
	 * and convert them into an object of type T.
	 *
	 * @param args Array of C-style strings representing command-line arguments.
	 * @return Parsed object of type T.
	 */
	virtual T parseData(char* args[]) const = 0;

	/**
	 * @brief Get the expected number of command-line arguments.
	 *
	 * This allows commands to validate the number of arguments
	 * before attempting to parse them.
	 *
	 * @return int Number of expected arguments.
	 */
	virtual int getArgCount() const = 0;

	/**
	 * @brief Get a description of the expected arguments.
	 *
	 * Provides a human-readable explanation of the arguments expected
	 * for parsing an object of type T.
	 *
	 * @return std::string Description of expected arguments.
	 */
	virtual std::string description() const = 0;

	/**
	 * @brief Validate the data or arguments.
	 *
	 * Implementations can perform checks to ensure the parsed data
	 * meets specific requirements.
	 *
	 * @return true if the data is valid, false otherwise.
	 */
	virtual bool validate() const = 0;


	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~IParser() = default;
};

#endif