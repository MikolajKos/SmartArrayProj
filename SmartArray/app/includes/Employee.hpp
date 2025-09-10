#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Represents an employee with personal and job-related information.
 */
class Employee {
	int id_;            /**< Employee ID */
	std::string name_;   /**< First name of the employee */
	std::string surname_;/**< Surname of the employee */
	std::string position_;/**< Job position/title */
	double salary_;     /**< Salary of the employee */
	int birthYear_;     /**< Year of birth */

public:
	/**
	* @brief Default constructor. Initializes empty employee.
	*/
	Employee();
	
	/**
	* @brief Parameterized constructor.
	* @param id Employee ID
	* @param name First name
	* @param surname Surname
	* @param position Job position/title
	* @param salary Employee salary
	* @param birthYear Year of birth
	*/

	Employee(
		int id, 
		std::string name, 
		std::string surname,
		std::string position,
		double salary,
		int birthYear
	);

	/**
	* @brief Destructor
	*/
	~Employee();

	// SETTERS
	/**
	* @brief Set the employee ID.
	* @param id New ID
	*/
	void setId(int id);

	/**
	* @brief Set the first name.
	* @param name New first name
	*/
	void setName(std::string name);

	/**
	* @brief Set the surname.
	* @param surname New surname
	*/
	void setSurname(std::string surname);

	/**
	* @brief Set the job position/title.
	* @param position New position
	*/
	void setPosition(std::string position);

	/**
	* @brief Set the employee salary.
	* @param salary New salary
	*/
	void setSalary(double salary);

	/**
	* @brief Set the birth year.
	* @param birthYear New birth year
	*/
	void setBirthYear(int birthYear);
	

	/**
	 * @brief Set all employee data at once.
	 *
	 * @param id Employee ID
	 * @param name First name
	 * @param surname Surname
	 * @param position Job position/title
	 * @param salary Employee salary
	 * @param birthYear Year of birth
	 */
	void setEmployee(
		int id,
		std::string name,
		std::string surname,
		std::string position,
		double salary,
		int birthYear
	);

	// METHODS
	/**
	* @brief Serialize the employee to a file stream.
	* @param os Output file stream
	* @param ob Employee to serialize
	*/
	friend void serialize(std::fstream& os, const Employee& ob);

	/**
	* @brief Deserialize the employee from a file stream.
	* @param is Input file stream
	* @param ob Employee to fill
	*/
	friend void deserialize(std::fstream& is, Employee& ob);

	// OPERATORS
	/**
	* @brief Stream output operator for Employee.
	* @param os Output stream
	* @param ob Employee to print
	* @return Reference to the output stream
	*/
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