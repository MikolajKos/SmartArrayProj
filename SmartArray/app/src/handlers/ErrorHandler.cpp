#include <iostream>
#include <handlers/ErrorHandler.hpp>

using namespace std;

const char* messages[] = {
	"E Memory allocation Error",
	"W Stack is full",
	"W Stack is empty"
};

void ErrorHandler::handler(enum Errors error, const char* info) {
	cout << messages[error] + 2 << endl;

	if (info != nullptr && info[0] != '\0') {
		cerr << info << endl;
	}

	if (messages[error][0] == 'E') {
		system("pause");
		exit(1);
	}
}