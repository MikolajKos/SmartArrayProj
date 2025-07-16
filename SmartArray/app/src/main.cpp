#include <iostream>
#include <string>
#include <crtdbg.h>
#include <commands/CommandHandler.hpp>
#include <Employee.hpp>
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

	//Employee e1(1, "Mikolaj", "Kosiorek", "Senior C++ developer", 40000, 2004);
	//Employee e2(1, "Piotr", "Kowalski", "Senior Java developer", 30000, 1998);
	//Employee e3(1, "Kamil", "Nowak", "Junior Python developer", 8000, 2002);
	//arr.push(e1);
	//arr.push(e2);
	//arr.push(e3);

	CommandHandler handler(arr);
	int result = handler.handle(argc, argv);
	if (result == 0) {
		SmartArrayIO<Employee>::save(arr);
	}

	return result;
}