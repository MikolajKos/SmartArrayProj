#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <string>

template <typename T>
class IParser {
public:
	virtual T parseData(char* args[]) const = 0;
	virtual int getArgCount() const = 0;
	virtual std::string description() const = 0;
	virtual bool validate() const = 0;
	virtual ~IParser() = default;
};

#endif