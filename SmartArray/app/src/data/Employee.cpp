#include <Employee.hpp>

Employee::Employee() : id_(-1), name_(), surname_(), position_(), salary_(-1), birthYear_(-1) {

}

Employee::Employee(
	int id,
	std::string name,
	std::string surname,
	std::string position,
	double salary,
	int birthYear) : id_(id), name_(name), surname_(surname), position_(position), salary_(salary), birthYear_(birthYear) {}

Employee::~Employee() {

}

void Employee::setId(int id) {
	id_ = id;
}
void Employee::setName(std::string name) {
	name_ = name;
}
void Employee::setSurname(std::string surname) {
	surname_ = surname;
}
void Employee::setPosition(std::string position) {
	position_ = position;
}
void Employee::setSalary(double salary) {
	salary_ = salary;
}
void Employee::setBirthYear(int birthYear) {
	birthYear_ = birthYear;
}

void Employee::setEmployee(
	int id,
	std::string name,
	std::string surname,
	std::string position,
	double salary,
	int birthYear
) {
	id_ = id;
	name_ = name;
	surname_ = surname;
	position_ = position;
	salary_ = salary;
	birthYear_ = birthYear;
}

void serialize(std::fstream& os, const Employee& ob) {
	size_t nameLen = ob.name_.length() + 1; // + 1 for '\0' sign in char pointer
	size_t surnameLen = ob.surname_.length() + 1;
	size_t positionLen = ob.position_.length() + 1;

	// Writing string lenghts
	os.write(reinterpret_cast<const char*>(nameLen), sizeof(size_t));
	os.write(reinterpret_cast<const char*>(surnameLen), sizeof(size_t));
	os.write(reinterpret_cast<const char*>(positionLen), sizeof(size_t));
	
	// Write data
	os.write(reinterpret_cast<const char*>(&ob.id_), sizeof(int));
	os.write(reinterpret_cast<const char*>(ob.name_.c_str()), nameLen);
	os.write(reinterpret_cast<const char*>(ob.surname_.c_str()), surnameLen);
	os.write(reinterpret_cast<const char*>(ob.position_.c_str()), positionLen);
	os.write(reinterpret_cast<const char*>(&ob.salary_), sizeof(double));
	os.write(reinterpret_cast<const char*>(&ob.birthYear_), sizeof(int));
}

void deserialize(std::fstream& is, Employee& ob) {
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
	is.read(reinterpret_cast<char *>(&ob.id_), sizeof(int));
	is.read(name, nameLen);
	is.read(surname, surnameLen);
	is.read(position, positionLen);
	is.read(reinterpret_cast<char *>(&ob.salary_), sizeof(double));
	is.read(reinterpret_cast<char*>(&ob.birthYear_), sizeof(int));

	// Copy buffors to Employee fields
	ob.setName(name);
	ob.setSurname(surname);
	ob.setPosition(position);

	// Delete buffor memory
	delete[] name; delete[] surname; delete[] position;
}

std::ostream& operator<<(std::ostream& os, const Employee& ob) {
	os << "Id: " << ob.id_ << std::endl
		<< "Name: " << ob.name_ << std::endl
		<< "Surname: " << ob.surname_ << std::endl
		<< "Position: " << ob.position_ << std::endl
		<< "Salary: " << ob.salary_ << std::endl
		<< "Birth Year: " << ob.birthYear_ << std::endl;

	return os;
}