#ifndef EMPLOYEE_PARSER_HPP
#define EMPLOYEE_PARSER_HPP

#include <Employee.hpp>
#include <vector>
#include <string>

/**
 * @brief Utility structure for parsing Employee data from command-line arguments.
 *
 * This struct provides static methods to parse Employee objects,
 * retrieve expected argument count, and get a description of arguments.
 */
struct EmployeeParser {
	
	/**
	* @brief Parse an Employee from command-line arguments.
	*
	* Skips the first two arguments (program and command name parameter)
	* and reads the next arguments to create an Employee object.
	*
	* @param args Array of C-style strings representing command-line arguments
	* @return Employee object constructed from arguments
	*/
	static Employee parseData(char* args[]) {
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
	static int getArgCount() { return 8; }

	/**
	* @brief Get a description of the expected command-line arguments.
	*
	* Returns a multi-line string explaining the number and type of arguments.
	*
	* @return std::string containing the description
	*/
	static std::string description() {
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