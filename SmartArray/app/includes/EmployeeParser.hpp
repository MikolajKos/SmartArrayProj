#ifndef EMPLOYEE_PARSER_HPP
#define EMPLOYEE_PARSER_HPP

#include <IParser.hpp>
#include <Employee.hpp>
#include <vector>
#include <string>

/**
 * @brief Parser for Employee objects from command-line arguments.
 *
 * This struct implements the IParser<Employee> interface and provides
 * functionality to parse Employee data, validate it, and supply metadata.
 * It encapsulates all type-specific logic for handling Employee input,
 * so command classes can remain generic and type-agnostic.
 *
 * @note Parsing assumes arguments are passed in the expected order:
 *       ID, First Name, Last Name, Position, Salary, Birth Year.
 *
 * Example usage:
 * @code
 * Employee e = EmployeeParser::parseData(argv);
 * int argc_expected = EmployeeParser::getArgCount();
 * std::string info = EmployeeParser::description();
 * @endcode
 */
struct EmployeeParser : public IParser<Employee>{
	
	/**
	* @brief Parse an Employee from command-line arguments.
	*
	* Skips the first two arguments (program and command name parameter)
	* and reads the next arguments to create an Employee object.
	*
	* @param args Array of C-style strings representing command-line arguments
	* @return Employee object constructed from arguments
	*/
	Employee parseData(char* args[]) const override {
		// Skip first two arguments
		return Employee{
			std::stoi(args[2]),
			args[3],
			args[4],
			args[5],
			std::stod(args[6]),
			std::stoi(args[7])
		};
	}

	/**
	* @brief Get the expected number of command-line arguments.
	* @return Integer representing the number of expected arguments
	*/
	int getArgCount() const override { return 8; }

	/**
	 * @brief Validate the parsed data.
	 *
	 * This method checks whether the parsed data meets the required conditions.
	 * Specific validation rules are defined by the specific parser implementation.
	 *
	 * @return true if the data is valid according to the parser's rules, false otherwise.
	 */
	bool validate() const override {
		return true;
	}

	/**
	* @brief Get a description of the expected command-line arguments.
	*
	* Returns a multi-line string explaining the number and type of arguments.
	*
	* @return std::string containing the description
	*/
	std::string description() const override {
		return R"(Number of arguments: 8
Arguments:
1. ID (integer)
2. First name (string)
3. Last name (string)
4. Position (string)
5. Salary (double)
6. Age (integer)
)";
	}
};

#endif