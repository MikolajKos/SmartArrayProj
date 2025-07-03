#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <string>

class Employee {
	int id_;
	std::string name_;
	std::string surname_;
	std::string position_;
	double salary_;
	int birthYear_;

public:
	Employee();
	Employee(
		int id, 
		std::string name, 
		std::string surname,
		std::string position,
		double salary,
		int birthYear
	);
	~Employee();

	// Setters
	void setId(int id);
	void setName(std::string name);
	void setSurname(std::string surname);
	void setPosition(std::string position);
	void setSalary(double salary);
	void setBirthYear(int birthYear);

	// Methods


	// Operators
	friend std::ostream& operator<<(std::ostream& os, const Employee& ob);
};

#endif