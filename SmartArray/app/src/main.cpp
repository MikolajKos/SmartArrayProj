#include <iostream>
#include <string>
#include <commands/CommandHandler.hpp>
#include <Employee.hpp>
#include <EmployeeParser.hpp>
#include <IParser.hpp>
#include <SmartArray.hpp>
#include <SmartArrayIO.hpp>

// #define DEBUG // Only for detecting memory leaks

int main(int argc, char* argv[]) {	
#if defined(DEBUG) && defined(_WIN32)
        #include <crtdbg.h>
  
        #define _CRTDBG_MAP_ALLOC
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // !DEBUGS
	SmartArray<Employee> arr;
	SmartArrayIO<Employee>::load(arr);

	EmployeeParser empParser;

	CommandHandler<Employee> handler(arr, empParser);
	int result = handler.handle(argc, argv);
	
	if (result == 0)
		SmartArrayIO<Employee>::save(arr);
	else if (result == 1)
		std::cout << "Something went wrong" << std::endl;

	return result;
}

// GENERAL NOTES

/*
*	"pushBack" command validation will be added
*/


// DOCUMENTATION NOTES

/*
*	Method return dictionary:
*		0 - success
*		1 - unknown error
*		2 - error described in error handlers
*/
