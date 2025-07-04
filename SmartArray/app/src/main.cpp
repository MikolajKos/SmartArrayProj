#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <string>
#include <SmartArray.hpp>
#include <Employee.hpp>
#include <crtdbg.h>

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SmartArray<Employee> sa;
	Employee e1(1, "Mikolaj", "Kosiorek", "Senior C++ Developer", 40000, 2004);
	Employee e2(2, "Jan", "Kowalski", "Senior Java Developer", 20000, 1999);
	Employee e3(3, "Agnieszka", "Radko", "Junior Python Developer", 8000, 2007);
	
	sa.push(e1);
	sa.push(e2);
	sa.push(e3);

	std::cout << sa;

	return 0;
}