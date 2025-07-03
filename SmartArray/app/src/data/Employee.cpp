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

std::ostream& operator<<(std::ostream& os, const Employee& ob) {
	os << "Id: " << ob.id_ << std::endl
		<< "Name: " << ob.name_ << std::endl
		<< "Surname: " << ob.surname_ << std::endl
		<< "Position: " << ob.position_ << std::endl
		<< "Salary: " << ob.salary_ << std::endl
		<< "Birth Year: " << ob.birthYear_ << std::endl;

	return os;
}