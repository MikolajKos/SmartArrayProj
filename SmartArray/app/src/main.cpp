#include <iostream>
#include <string>
#include <crtdbg.h>
#include <commands/CommandHandler.hpp>
#include <Employee.hpp>

#define DEBUG // Only for detecting memory leaks
#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[]) {	
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // !DEBUG
	SmartArray<Employee> arr;
	load(arr);

	CommandHandler handler(arr);
	return handler.handle(argc, argv);
}