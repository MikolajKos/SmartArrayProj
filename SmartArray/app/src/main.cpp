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
	load(sa);

	std::cout << sa;

	return 0;
}