#include <iostream>
#include <SmartArray.hpp>
#include <Employee.hpp>

int main(int argc, char* argv[]) {
	SmartArray<Employee> sa;
	Employee e1(1, "Mikolaj", "Kosiorek", "Senior C++ Developer", 40000, 2004);
	Employee e2(2, "Jan", "Kowalski", "Senior Java Developer", 20000, 1999);
	Employee e3(3, "Agnieszka", "Radko", "Junior Python Developer", 8000, 2007);
	
	sa.push(e1);
	sa.push(e2);
	sa.push(e3);

	std::cout << sa << std::endl;
}