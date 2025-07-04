#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

class ErrorHandler {
public:
	enum Errors {
		MEM_ALLOC_ERROR = 0,
		STACK_IS_FULL,
		STACK_IS_EMPTY,
		OPENING_FILE_ERROR,
		TOT_ERROR // Total number of errors 
	};

	static void handler(enum Errors error, const char* info = "");
};

#endif 