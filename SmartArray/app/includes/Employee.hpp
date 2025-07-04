#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <fstream>
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
	// Set All
	void setEmployee(
		int id,
		std::string name,
		std::string surname,
		std::string position,
		double salary,
		int birthYear
	);

	// Getters

	// Methods
	friend void serialize(std::fstream& os, const Employee& ob);
	friend void deserialize(std::fstream& is, Employee& ob);

	// Operators
	friend std::ostream& operator<<(std::ostream& os, const Employee& ob);
};

inline void serialize(std::fstream& os, const Employee& ob) {
	size_t nameLen = ob.name_.length() + 1;
	size_t surnameLen = ob.surname_.length() + 1;
	size_t positionLen = ob.position_.length() + 1;

	// Writing string lenghts
	os.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
	os.write(reinterpret_cast<const char*>(&surnameLen), sizeof(size_t));
	os.write(reinterpret_cast<const char*>(&positionLen), sizeof(size_t));

	// Write data
	os.write(reinterpret_cast<const char*>(&ob.id_), sizeof(int));
	os.write(reinterpret_cast<const char*>(ob.name_.c_str()), nameLen);
	os.write(reinterpret_cast<const char*>(ob.surname_.c_str()), surnameLen);
	os.write(reinterpret_cast<const char*>(ob.position_.c_str()), positionLen);
	os.write(reinterpret_cast<const char*>(&ob.salary_), sizeof(double));
	os.write(reinterpret_cast<const char*>(&ob.birthYear_), sizeof(int));
}

inline void deserialize(std::fstream& is, Employee& ob) {
	size_t nameLen, surnameLen, positionLen;

	// Reading string length
	is.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));
	is.read(reinterpret_cast<char*>(&surnameLen), sizeof(size_t));
	is.read(reinterpret_cast<char*>(&positionLen), sizeof(size_t));

	// Creating string buffors
	char* name = new char[nameLen];
	char* surname = new char[surnameLen];
	char* position = new char[positionLen];

	// Reading data: id, name, surename, position, salary, birthYear
	is.read(reinterpret_cast<char*>(&ob.id_), sizeof(int));
	is.read(name, nameLen);
	is.read(surname, surnameLen);
	is.read(position, positionLen);
	is.read(reinterpret_cast<char*>(&ob.salary_), sizeof(double));
	is.read(reinterpret_cast<char*>(&ob.birthYear_), sizeof(int));

	// Copy buffors to Employee fields
	ob.name_ = name;
	ob.surname_ = surname;
	ob.position_ = position;

	// Delete buffor memory
	delete[] name; delete[] surname; delete[] position;
}


#endif