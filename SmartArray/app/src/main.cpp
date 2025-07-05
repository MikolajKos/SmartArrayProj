#include <iostream>
#include <string>
#include <SmartArray.hpp>
#include <Employee.hpp>
#include <crtdbg.h>

#define DEBUG // Only for memory leaks
#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[]) {	
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // !DEBUG
	SmartArray<Employee> sa;
	//Employee e1(1, "Mikolaj", "Kosiorek", "Senior C++ Developer", 40000, 2004);
	//Employee e2(2, "Piotr", "Kowalski", "Senior Java Developer", 20000, 2002);

	//sa.push(e1);
	//sa.push(e2);

	//save(sa);

	load(sa);

	std::cout << sa;


	return 0;
}