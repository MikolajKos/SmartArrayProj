#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <string>

template <typename T>
class IParser {
public:
	virtual T parseData(char* args[]) = 0;
	virtual int getArgCount() = 0;
	virtual std::string description() = 0;
	virtual bool validate() = 0;
};

#endif