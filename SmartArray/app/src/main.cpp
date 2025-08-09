#include <iostream>
#include <string>
#include <crtdbg.h>
#include <commands/CommandHandler.hpp>
#include <Employee.hpp>
#include <EmployeeParser.hpp>
#include <SmartArray.hpp>
#include <SmartArrayIO.hpp>

#define DEBUG // Only for detecting memory leaks
#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[]) {	
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // !DEBUGS
	SmartArray<Employee> arr;
	SmartArrayIO<Employee>::load(arr);

	CommandHandler<Employee, EmployeeParser> handler(arr);
	int result = handler.handle(argc, argv);
	
	if (result == 0)
		SmartArrayIO<Employee>::save(arr);
	else if (result == 1)
		std::cout << "Something went wrong" << std::endl;

	return result;
}

// GENERAL NOTES

/*
*	"add" command validation will be added
*	Factory pattern will be implemented for creating dynamic Command objects
*/


// DOCUMENTATION NOTES

/*
*	Method return dictionary:
*		0 - success
*		1 - unknown error
*		2 - error described in error handlers
*/
