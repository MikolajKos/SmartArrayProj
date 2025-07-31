#ifndef EMPLOYEE_PARSER_HPP
#define EMPLOYEE_PARSER_HPP

#include <Employee.hpp>
#include <vector>
#include <string>

// Input validation will be implemented

struct EmployeeParser {
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

	static int getArgCount() { return 8; }
};

#endif