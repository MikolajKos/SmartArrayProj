#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

/**
 * @brief Handles general runtime errors in the SmartArray project.
 *
 * This class provides static methods and predefined error messages to handle
 * common runtime errors such as memory allocation failures, stack overflows,
 * empty collections, file access errors, or out-of-range indices.
 */
class ErrorHandler {
	static const char* messages[]; ///< Array of predefined error messages
public:
	/**
	 * @brief Enumeration of possible runtime errors.
	 */
	enum Errors {
		MEM_ALLOC_ERROR,   ///< Memory allocation failure
		STACK_IS_FULL,     ///< Attempt to push element into a full stack/array
		STACK_IS_EMPTY,    ///< Attempt to pop or print from an empty stack/array
		OPENING_FILE_ERROR,///< Error opening a file for read/write
		INDEX_OUT_OF_RANGE,///< Index accessed is out of valid range
		TOT_ERROR          ///< Total number of errors defined
	};	

	/**
	 * @brief Handle a runtime error.
	 *
	 * Prints or logs the appropriate error message based on the error type.
	 * An optional info string can provide additional context.
	 *
	 * @param error The type of error (from Errors enum)
	 * @param info Optional additional information about the error
	 */
	static void handler(enum Errors error, const char* info = "");
};

#endif